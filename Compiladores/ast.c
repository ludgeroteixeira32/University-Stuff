#include "ast.h"

int name_count = 0;

item *get_id(item_repository * item_rpst_local , char *s){
  item *item_local = create_item(s);
  insert_repository(item_rpst_local , item_local);
  return item_local;
}

item *get_id_both(char *s){
  item *item_local = create_item(s);
  insert_repository(item_rpst , item_local);
  insert_repository(item_rpst_find , item_local);
  return item_local;
}

EXPR *e_num (int n){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_NUM;
  e->id = malloc(4);
  *e->id = -1;
  e->type.num = n;
  e->left = e->right = NULL;
  return (e); 
}

EXPR *e_expr (EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_EXPR;
  e->left = NULL;
  e->id = malloc(4);
  *e->id = -1;
  e->right = b;
  return (e);
}

EXPR *e_string (char *s){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_STRING;
  static int address = 0;
  e->id = malloc(4);
  *e->id = -1;
  e->type.string = malloc(sizeof(s) - 2);
  for(int i = 1 ; i < strlen(s) - 1 ; i++){
    e->type.string[i-1] = s[i];
  }
  e->left = e->right = NULL;
  return (e);
}

EXPR *e_id (char *s){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;
  item *item = get_id(item_rpst_find , s);
  e->id = &item->id;
  e->left = e->right = NULL;
  e->print = malloc(4);
  *e->print = true;
  return (e);
}

void assign_id(int *id , EXPR *b){
  if (b != NULL){
    if (*b->id == -1){
      b->id = id;
      assign_id(id , b->left);
      assign_id(id , b->right);
    }
  }
}

EXPR *e_assign (char *s, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;
  item *item = get_id(item_rpst , s);
  e->id = &item->id;
  item->type = TYPE_INT;
  e->right = b;
  assign_id(e->id , e->right);
  e->left = NULL;
  e->print = malloc(4);
  *e->print = true;
  to_print(e->right , &e->print);
  return (e);
}

EXPR *e_assign_array_num (char *s, int size){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;
  item *item = get_id(item_rpst , s);
  e->id = &item->id;
  item->type = TYPE_INT_POINTER;
  e->variable = false;
  e->type.num = size;
  e->right = e->left = NULL;
  e->print = malloc(4);
  *e->print = true;
  return (e);
}

EXPR *e_assign_array_str (char *s, char *size){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;
  item *item = get_id(item_rpst , s);
  e->id = &item->id;
  item->type = TYPE_INT_POINTER;
  e->variable = true;
  e->type.string = strdup(size);
  e->right = e->left = NULL;
  e->print = malloc(4);
  *e->print = true;
  return (e);
}

EXPR *e_assign_array_num_find (char *s, int size){
  
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;
  item *item = get_id(item_rpst_find , s);
  e->id = &item->id;
  item->type = TYPE_INT_POINTER;
  e->variable = false;
  e->type.num = size;
  e->right = e->left = NULL;
  e->print = malloc(4);
  *e->print = true;
  return (e);
}

EXPR *e_assign_array_str_find (char *s, char *size){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;

  item *item = get_id(item_rpst_find , s);
  e->id = &item->id;
  item->type = TYPE_INT_POINTER;
  e->variable = true;
  e->type.string = strdup(size);
  e->right = e->left = NULL;
  e->print = malloc(4);
  *e->print = true;
  return (e);
}

EXPR *e_array_value_num (char *s, int pos , EXPR* value){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_ARRAY_VALUE;
  item *item = get_id(item_rpst_find , s);
  e->id = &item->id;
  e->left = NULL;
  e->right = value;
  e->variable = false; 
  e->type.num = pos;
  assign_id(e->id , e->right);
  e->print = malloc(4);
  *e->print = true;
  to_print(e->right , &e->print);
  return (e);
}

EXPR *e_array_value_str (char *s, char *pos , EXPR* value){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_ARRAY_VALUE;
  item *item = get_id(item_rpst_find , s);
  e->id = &item->id;
  e->left = NULL;
  e->right = value;
  e->variable = true; 
  e->type.string = strdup(pos);
  assign_id(e->id , e->right);
  e->print = malloc(4);
  *e->print = true;
  to_print(e->right , &e->print);
  return (e);
}

EXPR *e_assign_string (char *s, EXPR *right){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;
  item *item = get_id(item_rpst , s);
  e->id = &item->id;
  item->type = TYPE_STRING;
  item->value.string = malloc(sizeof(right->type.string));
  for(int i = 0 ; i < strlen(right->type.string); i++){
    item->value.string[i] = right->type.string[i];
  }
  e->left = NULL;
  e->right = right;
  assign_id(e->id , e->right);
  e->print = malloc(4);
  *e->print = true;
  to_print(e->right , &e->print);
  return (e);
}

void to_print(EXPR *e , bool **b){
  if (e != NULL){
      e->print = *b;
      to_print(e->left , b);
      to_print(e->right , b);
  }
}

EXPR *e_print_arit (EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_PRINT;
  e->id = malloc(4);
  *e->id = -1;
  e->right = b;
  e->print = malloc(4);
  *e->print = false;
  to_print(e->right , &e->print);
  e->left = NULL;
  return (e);
}

EXPR *e_print_string (char *s){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_PRINT_STRING;
  e->id = malloc(4);
  *e->id = -1;
  e->type.string = malloc(sizeof(s) - 2);
  for(int i = 1 ; i < strlen(s) - 1 ; i++){
    e->type.string[i-1] = s[i];
  }
  e->right = e->left = NULL;
  return (e);
}

EXPR *e_abs (EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_FUNC_ABS;
  e->id = malloc(4);
  *e->id = -1;
  e->left = NULL;
  e->right = NULL;
  e->args = malloc (sizeof (EXPR));
  e->args[0] = b;
  return (e);
}

EXPR *e_pot (EXPR *b, EXPR *c){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_FUNC_POT;
  e->id = malloc(4);
  *e->id = -1;
  e->left = NULL;
  e->right = NULL;
  e->args = malloc (2* sizeof (EXPR));
  e->args[0] = b;
  e->args[1] = c;
  return (e);
}

EXPR *e_fact (EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_FUNC_FACT;
  e->id = malloc(4);
  *e->id = -1;
  e->left = NULL;
  e->right = NULL;
  e->args = malloc (sizeof (EXPR));
  e->args[0] = b;
  return (e);
}

void local_var(hashtable *hash_table_local , EXPR *s){

  if(s != NULL){
    
    local_var(hash_table_local , s->right);
  }

}

STMT *s_def (char *s , EXPR *b , SLIST *c){
  STMT *st = malloc (sizeof (*st));
  st->st = ST_DEF;
  item *item = get_id(item_rpst , s);
  st->id = &item->id;
  item->type = TYPE_FUNC;
  st->expr = b;
  st->body = c;
  item->hash_table_local = create_table(11);
  local_var(item->hash_table_local , b);
  return (st);

}

EXPR *e_args_last (char *s){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;
  e->id = malloc(4);
  *e->id = -1;
  e->type.string = strdup(s);
  e->left = NULL;
  e->right = NULL;
  return (e);
}

EXPR *e_args (char *s , EXPR *next){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;
  e->id = malloc(4);
  *e->id = -1;
  e->type.string = strdup(s);
  e->left = NULL;
  e->right = next;
  return (e);
}

EXPR *e_mais (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_MAIS;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_menos (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_MENOS;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_vezes (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VEZES;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_div (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_DIV;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_mod (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_MOD;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

ASTNODE *st_par (STMT *e, ASTNODE *resto){
  ASTNODE *es = malloc (sizeof (*es));
  es->stmt = e;
  es->next = resto;
  return (es);
}

EXPR *e_equal(EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_EQ;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_notequal (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_NE;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_greater (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_G; 
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_less (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_L;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_greaterequal (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_GE;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_lessequal (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_LE;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_and (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_AND;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_or (EXPR *a, EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_OR;
  e->id = malloc(4);
  *e->id = -1;
  e->left = a;
  e->right = b;
  return (e);
}

EXPR *e_not (EXPR *b){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_NOT;
  e->id = malloc(4);
  *e->id = -1;
  e->left = NULL;
  e->right = b;
  return (e);
}

STMT *s_if (EXPR *b , SLIST *t , SLIST *e){
  STMT *s = malloc (sizeof (*s));
  s->st = ST_IF;
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "FU%dNC", name_count);
  name_count++;
  item *item = get_id(item_rpst , buffer);
  get_id(item_rpst_find , buffer);
  s->id = &item->id;
  item->type = TYPE_FUNC;
  s->expr = b;
  s->ifthen = t;
  s->ifelse = e;
  return (s);
}

STMT *s_while (EXPR *b , SLIST *c){
  STMT *s = malloc (sizeof (*s));
  s->st = ST_WHILE;
  s->expr = b;
  s->body = c;
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "FU%dNC", name_count);
  name_count++;
  item *item_id = get_id(item_rpst , buffer);
  get_id(item_rpst_find , buffer);
  s->id = &item_id->id;
  item_id->type = TYPE_FUNC;
  return (s);
}

STMT *s_for (EXPR *attribution , EXPR *condition , EXPR *increment , SLIST *c){
  STMT *s = malloc (sizeof (*s));
  s->st = ST_FOR;
  s->expr = condition;
  s->body = c;
  s->atrb = attribution;
  s->inc = increment;
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "FU%dNC", name_count);
  name_count++;
  item *item_id = get_id(item_rpst , buffer);
  get_id(item_rpst_find , buffer);
  s->id = &item_id->id;
  item_id->type = TYPE_FUNC;
  return (s);
}

STMT *s_pfor (EXPR *value , char *array, SLIST *c){
  STMT *s = malloc (sizeof (*s));
  s->st = ST_PFOR;
  s->body = c;
  s->extra = value;
  s->var = malloc(4);
  s->id = malloc(4);
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "FU%dNC", name_count);
  name_count++;
  item *item_id = get_id(item_rpst , buffer);
  get_id(item_rpst_find , buffer);
  s->id = &item_id->id;
  item_id->type = TYPE_FUNC;
  return (s);
}

EXPR *e_id_pfor (char *s){
  EXPR *e = malloc (sizeof (*e));
  e->op = EXPR_VAR;
  item *item = get_id(item_rpst , s);
  e->id = &item->id;
  item->instantiated = true;
  item->type = TYPE_INT;
  e->left = e->right = NULL;
  e->print = malloc(4);
  *e->print = true;
  return (e);
}

STMT *s_expr (EXPR *b){
  STMT *s = malloc (sizeof (*s)); 
  s->st = ST_EXPR;
  s->expr = b;
  return (s);
}

STMT *s_stmt (STMT *st){
  STMT *s = malloc (sizeof (*s)); 
  s->st = ST_STMT;
  s->stmt = st;
  return (s);
}


SLIST *sl_par (STMT *s, SLIST *resto){
  SLIST *es = malloc (sizeof (*es));
  es->s = s;
  es->next = resto;
  return (es);
}

int nl = 0;

void print_e(EXPR *expr , FILE *f , FILE *c){
    int xl;
    switch (expr->op) {

        case EXPR_FUNC_ABS:
          fprintf(f , "\tPUSH 0\n");
          print_e(expr->args[0] , f , c);
          fprintf(f , "\tPUSH abs\n");
          fprintf(f , "\tCALL\n");
          fprintf(f , "\tPOP\n");
          break;
        
        case EXPR_FUNC_FACT:
          fprintf(f , "\tPUSH 0\n");
          print_e(expr->args[0] , f , c);
          fprintf(f , "\tPUSH fact\n");
          fprintf(f , "\tCALL\n");
          fprintf(f , "\tPOP\n");
          break;

        case EXPR_FUNC_POT:
          fprintf(f , "\tPUSH 0\n");
          print_e(expr->args[0] , f , c);
          print_e(expr->args[1] , f , c);
          print_e(expr->args[1] , f , c);
          fprintf(f , "\tPUSH pot\n");
          fprintf(f , "\tCALL\n");
          fprintf(f , "\tPOP\n");
          fprintf(f , "\tPOP\n");
          fprintf(f , "\tPOP\n");
          break;

        case EXPR_PRINT:
          print_e(expr->right , f , c);
          if (*expr->print == false){
            fprintf(f , "\tDUP\n\tPUSH print_int\n\tCALL\n\tPOP\n");
            *expr->print = true;
          }
          break;
        
        case EXPR_PRINT_STRING:
          if (*expr->id == -1){
            for(int i = 0 ; i < strlen(expr->type.string) ; i++){
              fprintf(f , "\tPUSH %d\n", expr->type.string[i]);
              fprintf(f , "\tPUSH print_char\n\tCALL\n\tPOP\n");
            }
          }
          break;

        case EXPR_ARRAY_VALUE:
          print_e(expr->right , f , c);
          if (expr->variable == true){
            fprintf(f , "\tPUSH %s\n", expr->type.string);
            fprintf(f , "\tLOAD\n");
          }else{
            fprintf(f , "\tPUSH %d\n", expr->type.num);
          }
          fprintf(f , "\tPUSH %s\n", hash_table->items[*expr->id]->name);
          fprintf(f , "\tADD\n");
          fprintf(f , "\tSTORE\n");
          
          break;

        case EXPR_EXPR:
          print_e(expr->right , f , c);
          break;

        case EXPR_NUM:
            if (*expr->id != -1){
              if (hash_table->items[*expr->id]->instantiated == false){
                fprintf(c , "%s: .space %d\n" , hash_table->items[*expr->id]->name  ,1);
                hash_table->items[*expr->id]->instantiated = true;
              }
              
            }
            fprintf(f , "\tPUSH %d\n", expr->type.num);
            break;

        case EXPR_STRING:
          if (*expr->id != -1){
            if (hash_table->items[*expr->id]->instantiated == false){
              fprintf(c , "%s: " , hash_table->items[*expr->id]->name);
              for(int i = 0 ; i < strlen(expr->type.string) ; i++){
                fprintf(c , "\t.word %d\n " , (int)expr->type.string[i]);
              }
              fprintf(c , "\n");
              hash_table->items[*expr->id]->instantiated = true;
            }
          }
          break;

        case EXPR_VAR:
          if (expr->right != NULL){
              print_e (expr->right ,  f  , c);
              if (hash_table->items[*expr->id]->instantiated == false){
                fprintf(c , "%s: .space %d\n" , hash_table->items[*expr->id]->name , 1);
                hash_table->items[*expr->id]->instantiated = true;
              }
              if (hash_table->items[*expr->id]->type == TYPE_INT){
                fprintf(f , "\tPUSH %s\n", hash_table->items[*expr->id]->name);
                fprintf(f , "\tSTORE\n");
              }
          }else{
              
              if(hash_table->items[*expr->id]->type == TYPE_INT){
                if (*expr->id != -1){
                  fprintf(f , "\tPUSH %s\n", hash_table->items[*expr->id]->name);
                  fprintf(f , "\tLOAD\n");
                  if (*expr->print == false){
                    fprintf(f , "\tDUP\n\tPUSH print_int\n\tCALL\n\tPOP\n");
                    *expr->print = true;
                  }
                }

              }else if (hash_table->items[*expr->id]->type == TYPE_INT_POINTER){
                 if (*expr->id != -1){
                  if (hash_table->items[*expr->id]->instantiated == false && expr->variable == false){
                    fprintf(c , "%s: .space %d\n" , hash_table->items[*expr->id]->name , expr->type.num);
                    hash_table->items[*expr->id]->instantiated = true;
                    hash_table->items[*expr->id]->value.num = expr->type.num;
                  }else if (hash_table->items[*expr->id]->instantiated == true){
                    if (expr->variable == true){
                      fprintf(f , "\tPUSH %s\n", expr->type.string);
                      fprintf(f , "\tLOAD\n");
                    }else{
                      fprintf(f , "\tPUSH %d\n" , expr->type.num);
                    }
                    fprintf(f , "\tPUSH %s\n", hash_table->items[*expr->id]->name);
                    fprintf(f , "\tADD\n");
                    fprintf(f , "\tLOAD\n");
                    if (*expr->print == false){
                      fprintf(f , "\tDUP\n\tPUSH print_int\n\tCALL\n\tPOP\n");
                      *expr->print = true;
                    }
                  }
                }
              }else if(hash_table->items[*expr->id]->type == TYPE_STRING){
                if (*expr->id != -1){
                  if (*expr->print == false){
                    if (hash_table->items[*expr->id]->instantiated == true){
                      for(int i = 0 ; i < strlen(hash_table->items[*expr->id]->value.string) ; i++){
                        fprintf(f , "\tPUSH %d\n", i);
                        fprintf(f , "\tPUSH %s\n", hash_table->items[*expr->id]->name);
                        fprintf(f , "\tADD\n");
                        fprintf(f , "\tLOAD\n");
                        fprintf(f , "\tPUSH print_char\n\tCALL\n\tPOP\n");
                        *expr->print = true;
                      }
                    }

                  }else{

                    if (hash_table->items[*expr->id]->instantiated == true){
                      int totalvalue = 0;
                      for(int i = 0 ; i < strlen(hash_table->items[*expr->id]->value.string) ; i++){
                        totalvalue = totalvalue + (int)hash_table->items[*expr->id]->value.string[i];
                      }
                      fprintf(f , "\tPUSH %d\n", totalvalue);
                    }
                  }
                }
              }
          }
          break;

        case EXPR_MAIS:
            print_e (expr->left , f , c );
            print_e (expr->right , f , c );
            fprintf(f , "\tADD\n");
            //printf("+ ");
            break;
        case EXPR_MENOS:
            print_e (expr->left , f , c );
            print_e (expr->right , f , c );
            fprintf(f , "\tSUB\n");
            //printf("- ");
            break;
        case EXPR_VEZES:
            print_e (expr->left , f , c );
            print_e (expr->right , f , c );
            fprintf(f , "\tMUL\n");
            //printf("* ");
            break;
        case EXPR_DIV:
            print_e (expr->left , f , c );
            print_e (expr->right , f , c );
            fprintf(f , "\tDIV\n");
            //printf("/ ");
            break;
        case EXPR_MOD:
            print_e (expr->left , f , c );
            print_e (expr->right , f , c );
            fprintf(f , "\tMOD\n");
            //printf("%% ");
            break;
        case EXPR_EQ:
            //printf("[1 s/]s. 0 s/ ");
            xl = nl++;
            print_e (expr->left , f , c );
            fprintf(f , "\tDUP\n");
            fprintf(c , "ba%d: .space %d\n" , xl , 1);
            fprintf(f , "\tPUSH ba%d\n" , xl);
            fprintf(f , "\tSTORE\n");
            print_e (expr->right , f , c );
            fprintf(f , "\tDUP\n");
            fprintf(c , "ca%d: .space %d\n" , xl , 1);
            fprintf(f , "\tPUSH ca%d\n" , xl);
            fprintf(f , "\tSTORE\n");
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSUB\n");
            fprintf(f , "\tPUSH 0\n");
            fprintf(f , "\tSLT\n");
            fprintf(f , "\tPUSH L%dend\n" ,xl);
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSKIPZ\n");
            fprintf(f , "\tJUMP\n");
            fprintf(f , "\tPOP\n");
            fprintf(f , "\tPUSH ca%d\n" , xl);
            fprintf(f , "\tLOAD\n");
            fprintf(f , "\tPUSH ba%d\n" , xl);
            fprintf(f , "\tLOAD\n");
            fprintf(f , "\tSUB\n");
            fprintf(f , "\tPUSH 1\n");
            fprintf(f , "\tSLT\n");
            
            fprintf(f , "L%dend:\n" , xl);
            //printf("=. l/ ");
            break;
        case EXPR_NE:
            xl = nl++;
            //printf("[1 s/]s. 0 s/ ");
            print_e (expr->left , f , c );
            fprintf(f , "\tDUP\n");
            fprintf(c , "ba%d: .space %d\n" , xl , 1);
            fprintf(f , "\tPUSH ba%d\n" , xl);
            fprintf(f , "\tSTORE\n");
            print_e (expr->right , f , c );
            fprintf(f , "\tDUP\n");
            fprintf(c , "ca%d: .space %d\n" , xl , 1);
            fprintf(f , "\tPUSH ca%d\n" , xl);
            fprintf(f , "\tSTORE\n");
            fprintf(f , "\tSLT\n");
            fprintf(f , "\tDUP\n");
            fprintf(f , "\tPUSH L%dend\n" ,xl);
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSKIPZ\n");
            fprintf(f , "\tJUMP\n");
            fprintf(f , "\tPOP\n");
            fprintf(f , "\tPOP\n");
            fprintf(f , "\tPUSH ca%d\n" , xl);
            fprintf(f , "\tLOAD\n");
            fprintf(f , "\tPUSH ba%d\n" , xl);
            fprintf(f , "\tLOAD\n");
            fprintf(f , "\tSLT\n");
            fprintf(f , "L%dend:\n" , xl);

            //printf("!=. l/ ");
            break;
        case EXPR_LE:
            //printf("[1 s/]s. 0 s/ ");
            print_e (expr->left , f , c );
            print_e (expr->right , f , c );
            fprintf(f , "\tSUB\n");
            fprintf(f , "\tPUSH 1\n");
            fprintf(f , "\tSLT\n");
            //printf("!<. l/ ");
            break;
        case EXPR_GE:
            //printf("[1 s/]s. 0 s/ ");
            print_e (expr->left , f , c );
            print_e (expr->right , f , c );
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSUB\n");
            fprintf(f , "\tPUSH 1\n");
            fprintf(f , "\tSLT\n");
            //printf("!>. l/ ");
            break;
        case EXPR_L:
            //printf("[1 s/]s. 0 s/ ");
            print_e (expr->left , f , c );
            print_e (expr->right , f , c );
            fprintf(f , "\tSLT\n");
            //printf(">. l/ ");
            break; 
        case EXPR_G:
            //printf("[1 s/]s. 0 s/ ");
            print_e (expr->left , f , c );
            print_e (expr->right , f , c );
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSUB\n");
            fprintf(f , "\tPUSH 0\n");
            fprintf(f , "\tSLT\n");
            //printf("<. l/ ");
            break; 
        case EXPR_AND:
            //printf("[1 s/]s. 0 s/ ");
            xl = nl++;
            print_e (expr->left , f , c );
            fprintf(f , "\tDUP\n");
            fprintf(c , "ba%d: .space %d\n" , xl , 1);   
            fprintf(f , "\tPUSH ba%d\n" , xl);
            fprintf(f , "\tSTORE\n");
            print_e (expr->right , f , c );
            fprintf(f , "\tDUP\n");
            fprintf(c , "ca%d: .space %d\n" , xl , 1);
            fprintf(f , "\tPUSH ca%d\n" , xl);
            fprintf(f , "\tSTORE\n");
            fprintf(f , "\tSLT\n");
            fprintf(f , "\tPUSH 0\n");
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tPUSH L%dend\n" ,xl);
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSKIPZ\n");
            fprintf(f , "\tJUMP\n");
            fprintf(f , "\tPOP\n");  
            fprintf(f , "\tPUSH ca%d\n" , xl);
            fprintf(f , "\tLOAD\n");    
            fprintf(f , "\tPUSH ba%d\n" , xl);
            fprintf(f , "\tLOAD\n");
            fprintf(f , "\tSLT\n");
            fprintf(f , "\tPUSH 0\n");
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tPUSH L%dend\n" ,xl);
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSKIPZ\n");
            fprintf(f , "\tJUMP\n");
            fprintf(f , "\tPOP\n"); 
            fprintf(f , "\tPUSH ba%d\n" , xl);
            fprintf(f , "\tLOAD\n");
            fprintf(f , "L%dend:\n" , xl);
            //printf("s* l* =. [l* s^]s~ l/ 1 =~ l^ ");
            break;
        case EXPR_OR:
            //printf("[1 s/]s. 0 s/ ");
            xl = nl++;
            fprintf(f , "\tPUSH 1\n");
            print_e (expr->left , f , c );
            fprintf(f , "\tPUSH 1\n");
            print_e (expr->right , f , c );
            fprintf(f , "\tPUSH L%dend\n" ,xl);
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSKIPZ\n");
            fprintf(f , "\tJUMP\n");
            fprintf(f , "\tPOP\n");  
            fprintf(f , "\tPUSH L%dend\n" ,xl);
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSKIPZ\n");
            fprintf(f , "\tJUMP\n");
            fprintf(f , "\tPOP\n");
            fprintf(f , "\tPUSH 0\n");
            fprintf(f , "L%dend:\n" , xl);

            //printf("s* l* !=. 1 s^ [l* s^]s~ l/ 0 =~ l^ ");
            break; 
        case EXPR_NOT:
            xl = nl++;
            fprintf(f , "\tPUSH 0\n");
            print_e (expr->right , f , c );
            fprintf(f , "\tPUSH L%dend\n" ,xl);
            fprintf(f , "\tSWAP\n");
            fprintf(f , "\tSKIPZ\n");
            fprintf(f , "\tJUMP\n");
            fprintf(f , "\tPOP\n");
            fprintf(f , "\tPOP\n");
            fprintf(f , "\tPUSH 1\n");
            fprintf(f , "L%dend:\n" , xl);
            //printf("s* 1 s/ [0 s/]s. l* 1 =. l/ ");
            break;
    }

}

void print_next(SLIST *slist, FILE *f , FILE *c ){
  SLIST *temp = slist;
  while (temp != NULL){
    if (temp->s != NULL){
      if (temp->s->st == ST_EXPR){
        print_e(temp->s->expr , f , c );
      }else{
        print_cond(temp->s , f , c);
      }
    }
    temp = temp->next;
  }

}

void print_cond(STMT *stmt , FILE *f , FILE *c){
  switch (stmt->st){
    int xl;
    case ST_IF:
      xl = nl++;
      if (stmt->ifelse != NULL){
        print_e(stmt->expr , f , c);
        fprintf(f , "\tPUSH L%dthen\n" , xl);
        fprintf(f , "\tSWAP\n");
        fprintf(f , "\tSKIPZ\n");
        fprintf(f , "\tJUMP\n");
        fprintf(f , "\tPOP\n");  
        fprintf(f , "L%delse:\n" , xl); 
        print_next(stmt->ifelse , f , c);
        fprintf(f , "\tPUSH L%dend\n" ,xl);
        fprintf(f , "\tJUMP\n");
        fprintf(f , "L%dthen:\n" , xl); 
        if (stmt->ifthen != NULL)
          print_next(stmt->ifthen , f , c);
        fprintf(f , "L%dend:\n" , xl);
      }else{
        print_e(stmt->expr , f , c);
        fprintf(f , "\tPUSH L%dthen\n" , xl);
        fprintf(f , "\tSWAP\n");
        fprintf(f , "\tSKIPZ\n");
        fprintf(f , "\tJUMP\n");
        fprintf(f , "\tPOP\n");
        fprintf(f , "\tPUSH L%dend\n" ,xl);
        fprintf(f , "\tJUMP\n");
        fprintf(f , "L%dthen:\n" , xl);
        if (stmt->ifthen != NULL)
          print_next(stmt->ifthen , f , c);
        fprintf(f , "L%dend:\n" , xl); 
      }
        
      break;
    case ST_WHILE:
      xl = nl++;
      fprintf(f , "L%dstart:\n" , xl); 
      print_e(stmt->expr , f , c);
      fprintf(f , "\tPUSH L%ddo\n" , xl);
      fprintf(f , "\tSWAP\n");
      fprintf(f , "\tSKIPZ\n");
      fprintf(f , "\tJUMP\n");
      fprintf(f , "\tPOP\n");  
      fprintf(f , "\tPUSH L%dend\n" ,xl);
      fprintf(f , "\tJUMP\n");
      fprintf(f , "L%ddo:\n" , xl);
      if (stmt->body != NULL)
        print_next(stmt->body , f , c);
      fprintf(f , "PUSH L%dstart\n" , xl);
      fprintf(f , "\tJUMP\n");
      fprintf(f , "L%dend:\n" , xl); 
      break;

    case ST_FOR:
      xl = nl++;
      print_e(stmt->atrb , f , c);
      fprintf(f , "L%dstart:\n" , xl); 
      fprintf(f , "\tPUSH L%ddo\n" , xl);
      print_e(stmt->expr , f , c);
      fprintf(f , "\tSKIPZ\n");
      fprintf(f , "\tJUMP\n");
      fprintf(f , "\tPOP\n");  
      fprintf(f , "\tPUSH L%dend\n" ,xl);
      fprintf(f , "\tJUMP\n");
      fprintf(f , "L%ddo:\n" , xl);
      if (stmt->body != NULL)
        print_next(stmt->body , f , c);
      print_e(stmt->inc , f , c);
      fprintf(f , "PUSH L%dstart\n" , xl);
      fprintf(f , "\tJUMP\n");
      fprintf(f , "L%dend:\n" , xl); 
      break;

    case ST_PFOR:
      xl = nl++;
      fprintf(c , "%s: .space %d\n" , hash_table->items[*stmt->extra->id]->name , 1);
      fprintf(c , "pfor_array_position%d: .space %d\n" , xl, 1);
      fprintf(f , "\tPUSH 0\n");
      fprintf(f , "\tPUSH pfor_array_position%d\n", xl);
      fprintf(f , "\tSTORE\n");
      fprintf(f , "L%dstart:\n" , xl); 
      fprintf(f , "\tPUSH pfor_array_position%d\n", xl);
      fprintf(f , "\tLOAD\n");
      fprintf(f , "\tPUSH %s\n", hash_table->items[*stmt->var]->name);
      fprintf(f , "\tADD\n");
      fprintf(f , "\tLOAD\n");
      fprintf(f , "\tPUSH %s\n", hash_table->items[*stmt->extra->id]->name);
      fprintf(f , "\tSTORE\n");
      fprintf(f , "\tPUSH L%ddo\n" , xl);
      printf("%d\n" , hash_table->items[*stmt->var]->value.num);
      fprintf(f , "\tPUSH %d\n", hash_table->items[*stmt->var]->value.num);
      fprintf(f , "\tPUSH pfor_array_position%d\n", xl);
      fprintf(f , "\tLOAD\n");
      fprintf(f , "\tSUB\n");
      fprintf(f , "\tSKIPZ\n");
      fprintf(f , "\tJUMP\n");
      fprintf(f , "\tPOP\n");  
      fprintf(f , "\tPUSH L%dend\n" ,xl);
      fprintf(f , "\tJUMP\n");
      fprintf(f , "L%ddo:\n" , xl);
      if (stmt->body != NULL)
        print_next(stmt->body , f , c);
      fprintf(f , "\tPUSH pfor_array_position%d\n", xl);
      fprintf(f , "\tLOAD\n");
      fprintf(f , "\tPUSH 1\n");
      fprintf(f , "\tADD\n");
      fprintf(f , "\tPUSH pfor_array_position%d\n", xl);
      fprintf(f , "\tSTORE\n");
      fprintf(f , "\tPUSH L%dstart\n" , xl);
      fprintf(f , "\tJUMP\n");
      fprintf(f , "L%dend:\n" , xl); 
      break;

    case ST_COMP:
      break;
    
    case ST_EXPR:
      print_e(stmt->expr , f , c);
      break;

    default:
      break;
  }
  
}

void create_func(FILE *c, FILE *f){
  fprintf(f , "\tPUSH start\n");
  fprintf(f , "\tJUMP\n");

  fprintf(f , "pot:\n");
  fprintf(f , "\tPUSH 0\n");
  fprintf(f , "\tLINK\n");
  fprintf(f , "\tPUSH 1\n");   
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tLOAD\n"); 
  fprintf(f , "\tPUSH L3\n");
  fprintf(f , "\tSWAP\n");
  fprintf(f , "\tSKIPZ\n");    
  fprintf(f , "\tJUMP\n");
  fprintf(f , "\tPOP\n");
  fprintf(f , "\tPUSH 1\n");                                             
  fprintf(f , "\tPUSH 4\n");
  fprintf(f , "\tLOCAL\n");       
  fprintf(f , "\tSTORE\n");      
  fprintf(f , "\tUNLINK\n");
  fprintf(f , "\tJUMP\n");
  fprintf(f , "L3:\n");
  fprintf(f , "\tPUSH 0\n");
  fprintf(f , "\tPUSH 3\n"); 
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tLOAD\n");
  fprintf(f , "\tPUSH 2\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tLOAD\n");
  fprintf(f , "\tPUSH 1\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tLOAD\n");
  fprintf(f , "\tPUSH 1\n");
  fprintf(f , "\tSUB\n");
  fprintf(f , "\tPUSH pot\n");
  fprintf(f , "\tCALL\n");
  fprintf(f , "\tPOP\n");
  fprintf(f , "\tPOP\n");
  fprintf(f , "\tPOP\n");
  fprintf(f , "\tPUSH 3\n");    
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tLOAD\n");
  fprintf(f , "\tMUL\n");
  fprintf(f , "\tPUSH 4\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tSTORE\n");
  fprintf(f , "\tUNLINK\n");
  fprintf(f , "\tJUMP\n");


  fprintf(f , "fact:\n");
  fprintf(f , "\tPUSH 0\n");
  fprintf(f , "\tLINK\n");
  fprintf(f , "\tPUSH 1\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tLOAD\n");
  fprintf(f , "\tDUP\n");
  fprintf(f , "\tPUSH L1\n");
  fprintf(f , "\tSWAP\n");
  fprintf(f , "\tSKIPZ\n");
  fprintf(f , "\tJUMP\n");
  fprintf(f , "\tPOP\n");
  fprintf(f , "\tPOP\n");
  fprintf(f , "\tPUSH 1\n");
  fprintf(f , "\tPUSH 2\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tSTORE\n");
  fprintf(f , "\tUNLINK\n");
  fprintf(f , "\tJUMP\n");
  fprintf(f , "L1:\n");
  fprintf(f , "\tDUP\n");
  fprintf(f , "\tPUSH 0\n");
  fprintf(f , "\tSWAP\n");
  fprintf(f , "\tPUSH 1\n");
  fprintf(f , "\tSUB\n");
  fprintf(f , "\tPUSH fact\n");
  fprintf(f , "\tCALL\n");
  fprintf(f , "\tPOP\n");
  fprintf(f , "\tMUL\n");
  fprintf(f , "\tPUSH 2\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tSTORE\n");
  fprintf(f , "\tUNLINK\n");
  fprintf(f , "\tJUMP\n");


  fprintf(f , "abs:\n");
  fprintf(f , "\tPUSH 0\n");
  fprintf(f , "\tLINK\n");
  fprintf(f , "\tPUSH 0\n");
  fprintf(f , "\tPUSH 1\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tLOAD\n");
  fprintf(f , "\tSLT\n");
  fprintf(f , "\tPUSH LendABS\n");
  fprintf(f , "\tSWAP\n");
  fprintf(f , "\tSKIPZ\n");
  fprintf(f , "\tJUMP\n");
  fprintf(f , "\tPOP\n");
  fprintf(f , "\tPUSH -1\n");
  fprintf(f , "\tPUSH 1\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tLOAD\n");
  fprintf(f , "\tMUL\n");
  fprintf(f , "\tPUSH 2\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tSTORE\n");
  fprintf(f , "\tUNLINK\n");
  fprintf(f , "\tJUMP\n");
  fprintf(f , "LendABS:\n");
  fprintf(f , "\tPUSH 1\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tLOAD\n");
  fprintf(f , "\tPUSH 2\n");
  fprintf(f , "\tLOCAL\n");
  fprintf(f , "\tSTORE\n");
  fprintf(f , "\tUNLINK\n");
  fprintf(f , "\tJUMP\n");
  fprintf(f , "start:\n");


}

void add_to_hashtable(){

  item_rpst_node *temp_item_rpst = item_rpst->head;
  item_rpst_node *temp_item_rpst_find = item_rpst_find->head;
  int depth = 0;
  while (temp_item_rpst != NULL){

    if(strcmp(temp_item_rpst->itm->name, "START") == 0 ){
      depth++;
    }

    if (temp_item_rpst->itm->type == TYPE_FUNC){


    }

  }

}


void print_el(ASTNODE *node){
    FILE *f = fopen("body.sm" , "w");
    FILE *c = fopen("data.sm" , "w");
    if(f == NULL){
        //printf("Error: File does not exist");   
        exit(1);             
    }
    fprintf(c , ".data\n\n");
    fprintf(f , ".text\n");
    fprintf(f , "program:\n");
    create_func(c,f);

    print_item_repository(item_rpst);
    printf("next\n");
    print_item_repository(item_rpst_find);



    /*int isnum= 0;
    while(node != NULL){
      if (node->stmt != NULL){
        if (node->stmt->st == ST_EXPR){
          print_e(node->stmt->expr , f , c );
        }else{
          print_cond(node->stmt , f , c);
        }
      }
      node = node->next;
    }
    fclose(f);*/
    //printf("p\n");
   
}