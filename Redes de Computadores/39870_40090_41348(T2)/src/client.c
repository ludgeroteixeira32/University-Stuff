#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h> 
#include <stdlib.h>

#define BUFF_SIZE 550
#define INFINITE 1
#define PORT "5555"
#define LOCALHOST "127.0.0.1"
#define SIZE 1024
bool play;
char tictactoe[BUFF_SIZE];
pthread_t tid;

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

// Esta função imprime o tabuleiro de jogo
void print_ttt(char ttt[])
{
  int i;
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

char get_move(char ttt[])
{
  char move = 0;
  char buf[10];

  while (move < '1' || move > '9') {
    printf("A sua jogada? -> \n");
    fgets(buf, 5, stdin);
    move = buf[0];

    if (!try_play(ttt, move - '0', 0)) {
      printf("Esse lugar já está ocupado!\n");
      move = 0;
    }
  }

  return move;
}

void *ReceivedThread(void *vargp) 
{ 
  char response[BUFF_SIZE];
  int num_bytes;

  // Store the value argument passed to this thread 
  int *user_fd = (int *)vargp; 
  while(INFINITE)
  {
    num_bytes = recv(*user_fd, &response, sizeof(response), 0);
            
    if(play)
    {
      response[num_bytes]='\0';
      strcpy(tictactoe,response);
      print_ttt(response);
    }

    else
    {
      response[num_bytes]='\0';
      printf("%s", response);
   }
     
  }     

} 

// play's galo
void play_start(int user_fd)
{
  int i = -1;
  char request;

  while(i==-1) {

      char* response;

    print_ttt(tictactoe);
    request = get_move(tictactoe);

    send(user_fd, tictactoe, strlen(tictactoe), 0);

    i = check_win(tictactoe);

  }

  printf("Ganhou");
}

void send_file(FILE *fp, int sockfd)
{
    char data[SIZE] = {0};

    while(fgets(data, SIZE, fp)!=NULL)
    {
        if(send(sockfd, data, sizeof(data), 0)== -1)
        {
            perror("Erro ao enviar");
            exit(1);
        }
        bzero(data, SIZE);
    }
}

void file(int sockfd) {
  FILE *fp;
  char *filename = "file.txt";
  fp = fopen(filename, "r");
     if(fp == NULL)
     {
         perror("Erro ao tentar ler.");
         exit(1);
     }
     send_file(fp,sockfd);
     printf("Ficheiro enviado com sucesso. \n");
}


int main(void)
{
  struct addrinfo *add;
  char request[BUFF_SIZE];

  int user_fd;
  play = false;

  // read information about the server 
  getaddrinfo(LOCALHOST, PORT, NULL, &add); 
    
  // create socket that defines the domain to IP (IPv4 Internet protocols)
  user_fd = socket(AF_INET, SOCK_STREAM, 0); 

  // connect
  connect(user_fd, add->ai_addr, add->ai_addrlen);  
    
  printf("Operações Disponíveis:\n USERNAME nome\n MSSG mensagem\n JOIN nome\n FILE nome\n GALO nome\n Exit server-E\n\n" );

  pthread_create(&tid, NULL, ReceivedThread, (void *)&user_fd); 

  while(INFINITE)
  {

      fgets(request, BUFF_SIZE, stdin);  

      if(request[0] == 'E')
        break;

      if(request[0] == 'F')
      {
        request[strcspn(request, "\n")] = 0;
        send(user_fd, request, strlen(request), 0);
      
        file(user_fd);
        break;
      }

      if(request[0] != '\n')
      {
        request[strcspn(request, "\n")] = 0;
        send(user_fd, request, strlen(request), 0);
      }  

      if(request[0] == 'G')
      {
        play=true;
        play_start(user_fd);
      }
      

    }
    
  
  return 0;
}

