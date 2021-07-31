#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h> 

#include "canal.h"

#define NOT_REGIST -1
#define NOT_OPER 1

#define INFINITE 1
#define PORT "5555"
#define LOCALHOST "127.0.0.1"

#define NUMBER_OF_CANALS 4
#define CANAL_FOR_NEW_USERS 0


/*
  Create server socket
*/
int create_server_socket(struct addrinfo* add)
{
  int opt = 1;

  int server_fd = socket(AF_INET, SOCK_STREAM, 0); 
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
  bind(server_fd, add->ai_addr, add->ai_addrlen);
  listen(server_fd, 3);

  return server_fd;
}


/*
  Clear rset and add descriptor server_fd
    Return new max_fd (server_fd)
*/
int clear_and_add(fd_set* rset, int server_fd)
{
  FD_ZERO (rset);
  FD_SET(server_fd, rset);
    
  return server_fd;
}


/*
  Setup server.
*/
void setup_server(struct addrinfo* add, fd_set* rset, int* server_fd, int* max_fd)
{
  *server_fd = create_server_socket(add);
  *max_fd = clear_and_add(rset, *server_fd);
}


/*
  Add all users sockets to set and saves the max_fd
*/
void add_users_sockets_to_set(struct canal* canals[], fd_set* rset, int* max_fd)
{
  for (int i = 0; i < NUMBER_OF_CANALS; i++)   
    list_add_to_set(canals[i], rset, max_fd); 
}


/*
  Check if there's new connetions and saves new user
*/
void see_new_users(struct canal* canals[], struct addrinfo* add, fd_set* rset, int server_fd)
{
  //If something happened on the server_socket, then its an incoming connection
  if (FD_ISSET(server_fd, rset))   
    {   
      socklen_t addrlen = add->ai_addrlen;
      int new_user_socket = accept(server_fd, add->ai_addr, &addrlen); 

      canal_insert(canals[CANAL_FOR_NEW_USERS], new_user_socket, "", "");
    }
}


/*
  Check if there's new requests.
*/
void see_new_request(struct canal* canals[], fd_set* rset, int server_fd)
{
  for (int i = 0; i < NUMBER_OF_CANALS; i++) 
    see_canal_requests(canals, i, rset);
}


int main(void)
{
  int server_fd, max_fd;
  fd_set rset;
  struct addrinfo *add;
  
  struct canal* canals[NUMBER_OF_CANALS];
  inicialize_canals(canals);

  getaddrinfo(LOCALHOST, PORT, NULL, &add);
  setup_server(add, &rset, &server_fd, &max_fd);

  while(INFINITE)
  {
    max_fd = clear_and_add(&rset, server_fd); 
    
    add_users_sockets_to_set(canals, &rset, &max_fd);
        
    select(max_fd + 1 , &rset , NULL , NULL , NULL); 
        
    see_new_users(canals, add, &rset, server_fd);

    see_new_request(canals, &rset, server_fd);
  }

  return 0;
}


