#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h> 


#include "aux_functions.h"

#define MAX_NAME_SIZE 9
#define NUMBER_OF_CANALS 3

#define NOT_VALID true
#define VALID false

#define NOT_FOUND NULL

#define NEW_NAME 0
#define CHANGE_NAME -1

#define WARNING_001 1
#define WARNING_002 2
#define WARNING_003 3
#define WARNING_004 4
#define WARNING_101 101
#define WARNING_102 102
#define WARNING_301 301
#define WARNING_302 302

/*
  Separate the request from the arguments.
*/
void separate_request(char* request, char* delimiter)
{
  strtok(request, delimiter);
}


/*
  Get next argument.
*/
char* get_next_argument()
{
  return strtok(NULL, " ");
}


/*
  Get all mssg.
*/
char* get_mssg()
{
  return strtok(NULL, "");
}

/*
  Send response to the user who did the request.
*/
void send_response(int response_cod, int user_fd, char* list)
{
  char* response;
  
  if(response_cod == WARNING_001)
    response = "Nome atribuído com sucesso.\n\n";
  else  if(response_cod == WARNING_002)
    response = "Cliente já existente\n\n"; 
  else if(response_cod == WARNING_003)
    response = "O nome do cliente não foi inserido\n\n"; 
  else if(response_cod == WARNING_101)
    response = "Mensagem enviada com sucesso.\n\n";
  else if(response_cod == WARNING_301)
    response = "Mudança de canal com sucesso\n\n";
  else  if(response_cod == WARNING_302)
    response = "Cliente não existente\n\n"; 
  

  send(user_fd, response, strlen(response), 0); 
}