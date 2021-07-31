#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"

typedef enum _EXPR_TYPE {
  EXPR_NUM,
  EXPR_ARRAY,
  EXPR_PRINT,
  EXPR_FUNC_ABS,
  EXPR_FUNC_FACT,
  EXPR_FUNC_POT,
  EXPR_PRINT_STRING,
  EXPR_ARRAY_VALUE,
  EXPR_EXPR,
  EXPR_STRING,
  EXPR_VAR,
  EXPR_MAIS, EXPR_MENOS, EXPR_VEZES, EXPR_DIV, EXPR_MOD,
  EXPR_AND , EXPR_OR, EXPR_NOT,
  EXPR_EQ, EXPR_NE, EXPR_L, EXPR_G, EXPR_GE , EXPR_LE 
} EXPR_TYPE;

typedef enum _ST {
  ST_IF,
  ST_WHILE, 
  ST_FOR,
  ST_PFOR,
  ST_COMP,
  ST_EXPR,
  ST_STMT,
  ST_DEF
} ST;

typedef struct _EXPR EXPR;
struct _EXPR {
  EXPR_TYPE op;
  union{
    int num;
    char *string;
  }type;
  int *id;
  EXPR **args;
  bool variable;
  bool *print;
  EXPR *left, *right;
};

typedef struct _SLIST SLIST; // forward decl

typedef struct _STMT STMT;
struct _STMT {
  ST st;
  int *id;
  int *var;
  STMT *stmt;
  EXPR *atrb;
  EXPR *inc;
  EXPR *expr; 
  EXPR *extra;
  SLIST *body; // Serve para o While e para o for
  SLIST *ifthen;
  SLIST *ifelse;
};

struct _SLIST {
  int *depth;
  STMT *s;
  SLIST *next;
};

typedef struct _ASTNODE ASTNODE;
struct _ASTNODE {    // let this be *N (ASTNODE *N)
  int *depth;
  STMT *stmt;  // M->u.expr_seq;
  ASTNODE *next;
};

void print_e(EXPR *expr , FILE *f , FILE *c);
void print_cond(STMT *stmt , FILE *f , FILE *c);
void print_el(ASTNODE *node );

ASTNODE *st_par (STMT *e, ASTNODE *resto);

int id(hashtable **hash_table_global , char *s);

EXPR *e_num (int n);
EXPR *e_id (char *s);
EXPR *e_string (char *s);
EXPR *e_expr (EXPR *b);

void assign_id(int *id , EXPR *b);
EXPR *e_assign (char *s, EXPR *b);
EXPR *e_assign_string (char *s, EXPR *b);
EXPR *e_assign_array_num (char *s, int size);
EXPR *e_assign_array_num_find (char *s, int size);
EXPR *e_assign_array_str (char *s, char *size);
EXPR *e_assign_array_str_find (char *s, char *size);
EXPR *e_array_value_num (char *s, int pos , EXPR* value);
EXPR *e_array_value_str (char *s, char *pos , EXPR* value);
item *get_id(item_repository * item_rpst_local , char *s);

EXPR *e_mais (EXPR *a, EXPR *b);
EXPR *e_vezes (EXPR *a, EXPR *b);
EXPR *e_div (EXPR *a, EXPR *b);
EXPR *e_menos (EXPR *a, EXPR *b);
EXPR *e_mod (EXPR *a, EXPR *b);
ASTNODE *st_par (STMT *e, ASTNODE *resto);

EXPR *e_equal(EXPR *a, EXPR *b);
EXPR *e_notequal (EXPR *a, EXPR *b);
EXPR *e_greater (EXPR *a, EXPR *b);
EXPR *e_less (EXPR *a, EXPR *b);
EXPR *e_greaterequal (EXPR *a, EXPR *b);
EXPR *e_lessequal (EXPR *a, EXPR *b);

EXPR *e_and (EXPR *a, EXPR *b);
EXPR *e_or (EXPR *a, EXPR *b);
EXPR *e_not (EXPR *b);

SLIST *sl_par (STMT *s, SLIST *resto);
STMT *s_if (EXPR *b , SLIST *t , SLIST *e);
STMT *s_while (EXPR *b , SLIST *c);
STMT *s_for (EXPR *a , EXPR *b , EXPR *i , SLIST *c);
STMT *s_pfor (EXPR *value , char *array, SLIST *c);
EXPR *e_id_pfor (char *s);
STMT *s_expr (EXPR *b);
STMT *s_stmt (STMT *s);


EXPR *e_print_arit (EXPR *b);
EXPR *e_print_string (char *s);
void to_print(EXPR *e , bool **b);
EXPR *e_abs (EXPR *b);
EXPR *e_pot (EXPR *b, EXPR *c);

EXPR *e_fact(EXPR *b);
EXPR *e_args (char *s , EXPR *next);
EXPR *e_args_last (char *s);
STMT *s_def (char *s , EXPR *b , SLIST *c);
item *get_id_both(char *s);

extern char* strdup(const char*);




