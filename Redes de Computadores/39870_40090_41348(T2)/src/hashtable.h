#include <stdbool.h>


struct hashtable;

struct hashtable* hashtable_new ();

void hashtable_destroy ();

bool hashtable_insert(char name[], int category, int canal_index);

bool strequal(char v1[], char v2[]);

void my_strcpy(char dest[], char src[]);

int hashtable_change_canal( char name[], int canal_index);

