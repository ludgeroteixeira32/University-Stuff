#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h> 
#include <unistd.h>

#include "hashtable.h"
#include "canal.h"
#include "aux_functions.h"

#define SIZE 1024
#define NILL 0
#define NOT_SOCKET 0
#define NOT_FOUND NULL

#define DELETED 3

#define NEW_NAME 0

#define NOT_EXIST -1
#define EXIST -2

#define BUFF_SIZE 550
#define MAX_NAME_SIZE 9
#define MAX_CLIENTS 30

#define NUM_CANALS 4

#define NEW_USERS "new_users"
#define DEFAULT "default"
#define PRIVATE "private"
#define GALO "galo"

#define NEW_USERS_INDEX 0
#define DEFAULT_INDEX 1
#define PRIVATE_INDEX 2
#define GALO_INDEX 3
#define MAX_BYTES_MSSG 512

#define WARNING_001 1
#define WARNING_002 2
#define WARNING_003 3
#define WARNING_101 101
#define WARNING_301 301
#define WARNING_302 302


/* User Node */
struct user_node 
{
  char name[MAX_NAME_SIZE];     // user's name
  int socket;                   // user's socket
  char name_private[MAX_NAME_SIZE];
  struct user_node *next;       // user's next node
};


/* Canal */
struct canal 
{
  struct user_node *header;     // canal's header
  char name[BUFF_SIZE];         // canal's name
  char tictactoe[9];
};


/*
  Allocates, inicialize and returns a new node.
*/
struct user_node *node_new(int socket, char name[], char name_private[], struct user_node *next)
{
  struct user_node *node = malloc(sizeof(struct user_node));
  
  my_strcpy(node->name, name);
  my_strcpy(node->name_private, name_private);
  node->socket = socket;
  node->next = next;
  return node;
}


/*
	Allocates, inicialize and returns a new canal.
*/
struct canal* canal_new(char name[])
{
  struct canal* c = malloc(sizeof(struct canal));
  my_strcpy(c->name, name);
  c -> header = node_new(NOT_SOCKET,  "" , "", NULL);
  char aux[9] = {2,2,2,2,2,2,2,2,2};
  my_strcpy(c->tictactoe, aux);
  return c;
}

/*
  Remove user from canal.
*/
void canal_remove(struct canal *list, int socket_to_remove)
{
  struct user_node *h = list -> header;
  struct user_node *h_previous = h;

  while(h -> next != NULL && h -> socket != socket_to_remove)
  {
    h_previous = h;
    h = h -> next;
  }

  if(h -> socket == socket_to_remove)
    h_previous -> next = h -> next;
}

/*
  Add the users sockets in the canal to set and saves the max_fd.
*/
void list_add_to_set(struct canal *list, fd_set* rset, int* max_fd)
{
  struct user_node *h = list -> header;
        
  while(h -> next != NULL)
  {
    FD_SET(h -> next -> socket, rset); 
    if(h -> next -> socket > *max_fd)   
      *max_fd = h -> next -> socket;
      
    h = h -> next;
  }
}


/*
	Join new user to canal.
*/
void canal_insert(struct canal* list, int new_socket, char name[], char name_private[])
{   
  struct user_node *h = list -> header;
     
  while(h -> next != NULL && h -> socket != new_socket)
    h = h -> next;

  if(h -> socket != new_socket)
  {
    struct user_node *new_node = node_new(new_socket, name, name_private, NULL);
    h -> next  = new_node;
  }
}


/*
  Inicialize array of canals.
*/
void inicialize_canals(struct canal* canals[])
{
  canals[0] = canal_new(NEW_USERS);
  canals[1] = canal_new(DEFAULT);
  canals[2] = canal_new(PRIVATE);
  canals[3] = canal_new(GALO);
}

/*
  Check if there's a user with equal name in the canal.
    Return found user.
*/
struct user_node* exist_user(struct canal* list, char* name)
{
  struct user_node *h = list -> header;
  
  while(h -> next != NULL)
  {
    if(strequal(h->next->name, name))
      return h->next;

    h = h -> next;
  }

  return NULL;
}

/*
  Finds the name of the user in the canals
*/
struct user_node* find_canal(struct canal* canals[], char* name)
{
  struct user_node* user;

  for(int i = 1; i<4; i++)
  {
    user = exist_user(canals[i], name);
    if(user != NULL)
      return user;
  }

  return NULL;
}

/*
  Send response to canal.
*/
void send_to_canal(struct canal* canal, char* messg)
{
  if(messg[0] == '\0')
    return;

  struct user_node *h = canal -> header;

  while(h -> next != NULL)
  {
    send(h -> next -> socket, messg, strlen(messg), 0); 
    h = h -> next;
  }
}


///////////////////////  Types of Requests  ///////////////////////

/*
  USERNAME- Adds a name to a client.
*/
int USERNAME_request(struct canal* canals[], int* canal_index, struct user_node* user, char* messg)
{
  char* name = get_next_argument();

  // finds the user in all the canal's
  struct user_node* user_aux = find_canal(canals, name);
  if(user_aux != NULL)
    return WARNING_002;
    
  if(name == NOT_FOUND)
    return WARNING_003;


  sprintf(messg, "server :> novo utilizador %s\n", name);

  //go to canal default
  canal_insert(canals[DEFAULT_INDEX], user->socket, name, "");
  canal_remove(canals[NEW_USERS_INDEX], user->socket);
    
  *canal_index =  1;

  hashtable_insert(name, 1, 1);

  return WARNING_001;
}


/*
   MSSG- sends message to the ative canal.
*/
int MSSG_request(struct canal* canals[], struct user_node* user, char* messg)
{
  char* mssg = get_mssg();

  // builds the message thats gonna be sent
  sprintf(messg, "%s :> %s\n", user->name, mssg);
  
  return WARNING_101;
}

/*
   JOIN- creates the private canal
*/
int JOIN_request(struct canal* canals[], int* canal_index, struct user_node* user, char* messg)
{
  char* name_private = get_next_argument();

  // finds the user in all the canal's
  struct user_node* user_private = find_canal(canals, name_private);
  if(user_private == NULL)
    return WARNING_302;

  //define and send string for the ative canal and leave
  sprintf(messg, "server :> %s deixou este canal\n", user->name);
  canal_remove(canals[*canal_index], user->socket);
  send_to_canal(canals[*canal_index], messg);

  //define string for the new ative canal and enter
  *canal_index = 2;

  sprintf(messg, "server :> %s entrou neste canal\n", user->name);
  // sets a private name to the client
  canal_insert(canals[2], user->socket, user->name, user_private->name);

  hashtable_change_canal(user->name, *canal_index);
  
  return WARNING_301;
}

/*
  GALO- Changes the active canal to the game one, and the communications will be 1-1
*/
int GALO_request(struct canal* canals[], int* canal_index, struct user_node* user, char* messg)
{
  char* name_private = get_next_argument();

  //finds all the users in the server
  struct user_node* user_private = find_canal(canals, name_private);
  if(user_private == NULL)
    return WARNING_302;

  //define and send string for the ative canal and leave
  sprintf(messg, "server :> %s deixou este canal\n", user->name);
  canal_remove(canals[*canal_index], user->socket);
  send_to_canal(canals[*canal_index], messg);

  //define string for the new ative canal and enter
  *canal_index = 3;
  sprintf(messg, "server :> %s entrou neste canal\n", user->name);


  canal_insert(canals[3], user->socket, user->name, user_private->name);
  hashtable_change_canal(user->name, *canal_index);

  return WARNING_301;
}
void FILE_request(struct canal* canals[], int* canal_index, struct user_node* user, char* messg)
{
    int n; 
    FILE *fp;
    char *filename = "file2.txt";
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if(fp==NULL)
    {
        perror("Error in creating file.");
        exit(1);
    }
    while(1)
    {
        n = recv(user->socket, buffer, SIZE, 0);
        if(n<=0)
        {
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    return;
    
}
void send_tab(struct canal* c, struct user_node* user, char* request){
  char tictactoe[10] = {2,2,2,2,2,2,2,2,2,0};
  send(user->socket, tictactoe, sizeof(tictactoe), 0);
}

/*
  Do the user request.
*/
void do_request(struct canal* canals[], int canal_index, struct user_node* user, char* request)
{
  int response;
  char messg[BUFF_SIZE];
  char list[BUFF_SIZE];
  list[0] = '\0';
  messg[0] = '\0';
  
  strcpy(list, request);
  separate_request(request, " ");

  int new_canal = canal_index;
  
  //see type of request
  if(strequal(request, "USERNAME"))
  {
    response = USERNAME_request(canals, &new_canal, user, messg);
    send_response(response, user->socket, list);
  }
  else if(strequal(request, "MSSG"))
  {
    response = MSSG_request(canals, user, messg);
    send_response(response, user->socket, list);
  }
    
  else if(strequal(request, "JOIN"))
    response = JOIN_request(canals, &new_canal, user, messg);
  else if (strequal(request, "GALO"))
  {
    response = GALO_request(canals, &new_canal, user, messg);
    send_tab(canals[GALO_INDEX], user, request);
  }
 else if (strequal(request, "FILE"))
 {
   FILE_request(canals, &new_canal, user, messg);
 }  
  else{
    response = WARNING_001;
  }

  struct user_node* user_private = find_canal(canals, user->name_private);

  if(canal_index == 3){
    strcpy(canals[3]->tictactoe, request);
    
  }
  else if(canal_index == 2 && strequal(request, "MSSG"))
  {
    send(user_private->socket, messg, strlen(messg), 0); 
  } else {
    //see if the messg is for the users in the canal
    send_to_canal(canals[1], messg);
  }

}


/*
  See of theres canal request.
*/
void see_canal_requests(struct canal* canals[], int canal_index, fd_set* rset)
{
  char request[BUFF_SIZE];
  int num_bytes;
  struct user_node *h = canals[canal_index] -> header;
        
  //see all sockets in the canal
  while(h != NULL && h -> next != NULL)
  {
    //see if there's some IO operation in the socket
    if(FD_ISSET(h->next->socket, rset))
    {
      //remove descriptor from set
      FD_CLR(h->next->socket, rset);
      
      //receive request from socket
      num_bytes = recv(h->next->socket, request, BUFF_SIZE, 0);
      request[num_bytes] = '\0'; 

      //check if somebody desconnected
      if(num_bytes == 0)
      {
        close(h->next->socket);
        canal_remove(canals[canal_index], h->next->socket);
      }
      //else do request
      else
        do_request(canals, canal_index, h->next, request);
    }

    h = h -> next;
  }
}


