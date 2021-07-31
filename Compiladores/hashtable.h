#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum _TYPE {
  TYPE_STRING,
  TYPE_INT,
  TYPE_INT_POINTER,
  TYPE_FUNC,
} TYPE;

typedef struct _item item;
typedef struct _item_repository item_repository;
typedef struct _item_rpst_node item_rpst_node;
typedef struct _hashtable hashtable;

struct _item{
    char *name;
    int id;
    int *depth;
    union{
      int num;
      char *string;
    }value;
    hashtable *hash_table_local;
    bool instantiated;
    TYPE type;
};

struct _item_rpst_node{
  item *itm;
  item_rpst_node *next;
};

struct _item_repository{
  int size;
  item_rpst_node *head;
};

struct _hashtable{
    int size;
    int count;
    item **items;
};

unsigned int hash_function(unsigned char *str , int size);
hashtable *create_table(int size);
item *create_item( char *name);
bool is_prime(int n);
void free_hashtable(hashtable *hashtable);
int next_prime(int n);
hashtable *rehash(hashtable *hash_table);
item *insert_value(hashtable **hashtable , item *item , int key);
void print_hashtable(hashtable * hashtable );

item_repository *create_item_repository();
item_rpst_node *create_item_repository_node(item *item);
void insert_repository(item_repository *rpst , item *item);
void print_item_repository(item_repository *rpst);

extern hashtable *hash_table;
extern item_repository *item_rpst;
extern item_repository *item_rpst_find;
extern char* strdup(const char*);