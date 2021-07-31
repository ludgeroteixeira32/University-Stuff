#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "hashtable.h"
#include "aux_functions.h"

#define NILL 0

#define NOT_EXIST -1
#define EXIST -2

#define DELETED 3

#define NOT_OPER 1
#define OPER 2

#define MAX_NAME_SIZE 9
#define BUFF_SIZE 550
#define HASHTABLE_SIZE 100

#define DEFAULT 1

#define NAME_FILE "2hashtable.dat"

/* Hashtable */
struct hashtable {
  FILE* fd;                 // file descriptor to the file that contains the hashtable
};


/* user */
struct user {
  char name[MAX_NAME_SIZE];     // user's name
  int category;                 // user's category
  int canal_index;              // user's favourite canal
};


/*
  Check if two strings are equal.  
    Return true if equal, else return false. 
*/
bool strequal(char v1[], char v2[])			
{		
	int i = 0;
	while (v1[i] == v2[i] && v1[i] != '\0' && v2[i] != '\0')
		i++;			
		
	return v1[i] == v2[i];
}


/*
    Copys string in src[] to des[].
*/
void my_strcpy(char dest[], char src[])			
{													
	int i;																				
	for(i=0; src[i] != '\0'; i++)
		dest[i] = src[i];

	dest[i] = '\0';
}


/*
	Inicialize a user s.
*/
void user_new(struct user* s, char name[], int category, int canal_index)
{
    my_strcpy(s->name, name);
    s->category = category;
    s->canal_index = canal_index;
}


/*
	Allocates and returns a new user uninitialized.
*/
struct user* user_new_empty()
{
    return malloc(sizeof(struct user));
}


/*
	Write a user s in the position of index in the hashtable h data file.  
*/
void user_write(struct hashtable* h, struct user* s, int index)
{
    fseek(h->fd, index * sizeof(struct user), SEEK_SET);
    fwrite (s, sizeof(struct user), 1, h->fd); 
}


/*
	Read a user s in the position of index in the hashtable h data file.  
    Returns the number of bytes read.
*/
size_t user_read(struct hashtable* h, struct user* s, int index)
{
    fseek(h->fd, index * sizeof(struct user), SEEK_SET);
    return fread (s, sizeof(struct user), 1, h->fd);
}


/*
	Read the next user s at the current position in the hashtable h data file.
    Returns the number of bytes read.
*/
size_t user_read_next(struct hashtable* h, struct user* s)
{
    return fread (s, sizeof(struct user), 1, h->fd);
}


/*
	Destruction of user s. 
*/
void user_destroy(struct user* s)
{
    free(s); //Free memory space
}


/*
	Open hashtable h's data file.
    Save the file descriptor in the struct hashtable h.
*/
void hashtable_open(struct hashtable* h, char name[])
{
    h->fd = fopen(name, "rb+");

    if (h->fd != NULL)
        return;

    h->fd = fopen(name, "wb+");
}


/*
	Close hashtable h's data file.
*/
void hashtable_close(struct hashtable* h)
{
    fclose (h->fd);
}


/*
	Creation of hashtable h and allocation in memory.
*/
struct hashtable* hashtable_new ()
{
    struct hashtable* h = malloc(sizeof(struct hashtable));
    hashtable_open(h, NAME_FILE);
    return h;
}


/*
	Destruction of hashtable h and freeing memory.
*/
void hashtable_destroy (struct hashtable* h)
{
    hashtable_close(h);
    free(h);
}


/*
    Creation of a key for the given user's identification.
*/
int hashcode (char name[])
{
    int value = 0;
    int l = strlen(name);
    for(int i = 0; i < l; i++)
        value += 31*value + name[i];

    value %= HASHTABLE_SIZE;
    // In case value became negative
    if(value < 0)
        value += HASHTABLE_SIZE;

    return value % HASHTABLE_SIZE;
}


/*
    Search a user with the given name in the hashtable h or a empty space for a new user.
    Returns index of a empty space for a new user or a negative number in case that user already exist.
*/
int hashtable_search_user_or_empty_space(struct hashtable* h, struct user* s, char ident[])
{
    int key = hashcode(ident);
    size_t num_bytes = user_read(h, s, key);

    int key_deleted = NOT_EXIST;

    // Cycle goes until is found a user with equal identification or a position NILL
    for(key = key+1; num_bytes != 0 && s->category != NILL && !strequal(s->name, ident); key++)
    {
        // If is found a user deleted, the key is saved for the new user
        if(s->category == DELETED && key_deleted == NOT_EXIST)
            key_deleted = key;

        // In case is reach the end of the hashtable h 
        if(key >= HASHTABLE_SIZE)
            rewind(h->fd);

        num_bytes = user_read_next(h, s);
    }
    
    if (key_deleted != NOT_EXIST)
        key = key_deleted;

    if(num_bytes == 0 || (s->category == NILL || s->category == DELETED))
        return ((key-1) % HASHTABLE_SIZE);    

    return EXIST;
}


/*
    Insert a new user into hashtable h.
    Returns true if the user is inserted, else, the user already exist, return false.
*/
bool hashtable_insert(char name[], int category, int canal_index)
{  
    struct hashtable* h = hashtable_new ();

    struct user* s = user_new_empty();
    int index = hashtable_search_user_or_empty_space(h, s, name);

    if(index == EXIST)
    {
        hashtable_destroy (h);
        user_destroy(s);
        return false;
    }
    
    user_new(s, name,category, canal_index);
    user_write(h, s, index);
    user_destroy(s);
    
    hashtable_destroy (h);
    return true;
}


/*
    Search a user with the given name in the hashtable h.
    Returns index of that user in the hashtable or a negative number in case that user don't exist. 
*/
int hashtable_search_user(struct hashtable* h, struct user* s, char name[])
{
    int key = hashcode(name);
    size_t num_bytes = user_read(h, s, key);
    
    // Cycle goes until is found a user with equal identification or a position NILL
    for(key = key+1; num_bytes != 0 && s->category != NILL && !strequal(s->name, name); key++)
    {
        // In case is reach the end of the hashtable h 
        if(key >= HASHTABLE_SIZE)
            rewind(h->fd);

        num_bytes = user_read_next(h, s);
    }

    if(num_bytes == 0 || (s->category == NILL || s->category == DELETED))
        return NOT_EXIST;

    return ((key-1) % HASHTABLE_SIZE);
}




/*
	Change a user's favourite canal in the hashtable h.
    Return the unchanged index canal of that user or a negative number if that user don't exist.
*/
int hashtable_change_canal( char name[], int canal_index)
{
    struct hashtable* h = hashtable_new ();

    struct user* s = user_new_empty();
    int index = hashtable_search_user(h, s, name);

    if(index == NOT_EXIST)
    {
        user_destroy(s);
        hashtable_destroy (h);
        return NOT_EXIST;
    }

    s->canal_index = canal_index;
    user_write(h, s, index);

    user_destroy(s);

    hashtable_destroy (h);

    return canal_index;
}
