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

//Imprime o tabuleiro de jogo
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


//Tenta realizar uma jogada
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


//Verifica se existe um vencedor
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


// Inicializa uma jogada e verifica se a mesma é possível
char get_move(char ttt[])
{
  char move = 0;
  char buf[10];

  while (move < '1' || move > '9') {
    printf("A sua jogada? ->");
    fgets(buf, 5, stdin);
    move = buf[0];

    if (!try_play(ttt, move - '0', 1)) {
      printf("\nEsse lugar já está ocupado!\n");
      move = 0;
    }
  }

  return move;
}


// inicializa o tabuleiro
char tictactoe[9] = {2,2,2,2,2,2,2,2,2};


int main()
{
	int ssid;
	char moveC[2];
	int i;
	char mark;		

	ssid=socket(AF_INET,SOCK_STREAM,0);

	if(ssid==-1)
	{
		printf(" \nFalha na tentativa de criação do socket do lado do servidor\n");
		exit(0);
	}
	printf(" \nA criação do socket do lado do servidor foi feita com sucesso\n");
	int sid;
	struct sockaddr_in ssadd;
	ssadd.sin_family=AF_INET;
	ssadd.sin_port=htons(9000);
	ssadd.sin_addr.s_addr=inet_addr("127.0.0.1");
	sid=bind(ssid,(struct sockaddr*)&ssadd,sizeof(ssadd));
	if(sid==-1)
	{
		printf("\n Falha no binding do lado do servidor\n ");
		exit(0);
	}
	printf("\n Binding feito com sucesso do lado do servidor\n");

	listen(ssid,5);

	struct sockaddr_in fadd;
	socklen_t len=sizeof(fadd);
	int fd1=accept(ssid,(struct sockaddr*)&fadd,&len);
	if(fd1==(-1))
	{
		printf("\nFalha do lado do servidor\n");
		exit(0);
	}
	
	i= check_win(tictactoe);
	while(i==-1)
	{	
		// o servidor recebe uma mensagem/jogada do cliente
		recv(fd1,&moveC,sizeof(moveC),0);
		// caso essa mensagem seja um 'W', o servidor ganhou. 
		if(moveC[0] == 'W'){
			printf("Ganhamos");
			break;
		}

		//caso a jogada que o cliente esteja a tentar fazer, não for valida, o servidor manda um "X".
		if(try_play(tictactoe,moveC[0]-'0',0) == 0){
			char ocupado = 'X';
			printf("%c",ocupado);
			send(fd1,&ocupado,sizeof(ocupado),0);
		}

		//caso a jogada que o servidor recebe resulte numa vitória por parte do cliente, o servidor manda um "W.
		if(check_win(tictactoe)!= -1)
		{
			print_ttt(tictactoe);
			char win ='W';
			send(fd1,&win,sizeof(win),0);
			printf("O adversário ganhou");
			close(ssid);
			break;
		}

		//Caso uma situação de vitória seja verificada, é impresso o tabuleiro atualizado com essa vitória.
		if(check_win(tictactoe)!= -1)
		{
		print_ttt(tictactoe);
		close(ssid);
		break;
		}

		//O tabuleiro é impresso, e o servidor manda uma mensagem/jogada.
		print_ttt(tictactoe);
		char move = get_move(tictactoe);
		send(fd1,&move,sizeof(move),0);

		
	}	
	close(ssid);
	return 0;
}