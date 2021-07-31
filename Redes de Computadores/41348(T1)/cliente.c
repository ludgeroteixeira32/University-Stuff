#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

/*******************************************************************
                       Funções auxiliares ao jogo
 ********************************************************************/


// Esta função imprime o tabuleiro de jogo
void print_ttt(char ttt[])
{
  int i,
      l = 0;

  for (i = 0; i < 9; i++) {
    if (ttt[i] == 2) printf(" %d ", i+1);
    else if (ttt[i] == 0) printf (" X ");
    else if (ttt[i] == 1) printf (" O ");

    if (i == 2 || i == 5 || i == 8) printf("\n");
    if (i == 2 || i == 5) printf("---+---+---\n");
    if (i == 0 || i == 1 || i == 3 || i == 4 || i == 6 || i == 7) printf("|");
  }
  printf("\n");
}

//Esta função serve para se tentar fazer uma jogada
int try_play(char ttt[], int spot, char mark)
{
  spot = spot-1;
  if (ttt[spot] == 2) { // se o espaço tiver vazio, pode-se jogar nesse espaço
    ttt[spot] = mark;
    return 1;
  }
  else {
    return 0;
  }
}

//Está função verifica se existe um vencedor
int check_win(char ttt[])
{
  int who = -1;

  if (
      //linhas
      ((who = ttt[0]) == ttt[1] && ttt[1] == ttt[2] && who != 2) ||
      ((who = ttt[3]) == ttt[4] && ttt[4] == ttt[5] && who != 2) ||
      ((who = ttt[6]) == ttt[7] && ttt[7] == ttt[8] && who != 2) ||
      //colunas
      ((who = ttt[0]) == ttt[3] && ttt[3] == ttt[6] && who != 2) ||
      ((who = ttt[1]) == ttt[4] && ttt[4] == ttt[7] && who != 2) ||
      ((who = ttt[2]) == ttt[5] && ttt[5] == ttt[8] && who != 2) ||
      //diagonais
      ((who = ttt[0]) == ttt[4] && ttt[4] == ttt[8] && who != 2) ||
      ((who = ttt[2]) == ttt[4] && ttt[4] == ttt[6] && who != 2)
      )
    {
      return who;
    }
  else return -1;
}

//Esta função começa uma jogada e vê se a mesma é possível
char get_move(char ttt[])
{
  char move = 0;
  char buf[10];

  while (move < '1' || move > '9') {
    printf("A sua jogada? -> ");
    fgets(buf, 5, stdin);
    move = buf[0];

    if (!try_play(ttt, move - '0', 0)) {
      printf("Esse lugar já está ocupado!\n");
      move = 0;
    }
  }

  return move;
}

// inicialização do tabuleiro
char tictactoe[9] = {2,2,2,2,2,2,2,2,2};


int main()
{
	int csid;
	char moveS[2];
	int i;
	char mark;

	csid=socket(AF_INET,SOCK_STREAM,0);
	if(csid==-1)
	{
		printf(" Falha na tentativa de criação do socket do lado do servidor\n");
		exit(0);
	}
	printf(" A criação do socket do lado do servidor foi feita com sucesso\n");
	
	struct sockaddr_in csadd;
	csadd.sin_family=AF_INET;
	csadd.sin_port=htons(9000);
	csadd.sin_addr.s_addr=inet_addr("127.0.0.1");
	int c=connect(csid,(struct sockaddr*)&csadd,sizeof(csadd));
	if(c==0)
	{
		printf("Conexão establecida com sucesso\n\n");
	}
	if(c==(-1))
	{
		printf("Impossível conectar\n");
		exit(0);
	}

	i= check_win(tictactoe);
	while(i==-1)
	{
		//O tabuleiro é impresso e o cliente envia uma mensagem/jogada.
		print_ttt(tictactoe);
		char move = get_move(tictactoe);
		send(csid,&move,sizeof(move),0);

		//caso essa mensagem seja um 'W', o cliente ganhou.
		recv(csid,&moveS,sizeof(moveS),0);
		if(moveS[0] == 'W'){
			printf("Ganhamos!!");
			break;
		}

		//caso a jogada que o servidor esteja a tentar fazer, não for valida, o cliente manda um "X".
		if(try_play(tictactoe,moveS[0]-'0',1) == 0){
			char ocupado = 'X';
			printf("%c",ocupado);
			send(csid,&ocupado,sizeof(ocupado),0);
		}


		//caso a jogada que o cliente recebe resulte numa vitória por parte do servidor, o cliente manda um "W.
		if(check_win(tictactoe)!= -1)
		{
			print_ttt(tictactoe);
			char win ='W';
			send(csid,&win,sizeof(win),0);
			printf("O adversário ganhou");
			close(csid);
			break;
		}
		try_play(tictactoe,moveS[0]-'0',1);

		//Caso uma situação de vitória seja verificada, é impresso o tabuleiro atualizado com essa vitória.
		if(check_win(tictactoe)!= -1)
		{
		print_ttt(tictactoe);
		close(csid);
		break;
		}

		
	}	
	close(csid);
	return 0;
}
