%{ // -*- Bison -*-

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

void yyerror (char const *e) {
  fprintf (stderr, "ouch: %s\n", e);
  exit(1);
}

ASTNODE *a;

void yywrap() {}

int yylex(); // definido no lex


%}

%union{

  EXPR *expr;
  STMT *stmt;
  ASTNODE *astnode;
  SLIST *sl;
  char *id;
  int i;
  char *s;
}


%type <expr> expr func arit cmpr oper strn ptrn args atrb vari
%type <sl> slst
%type <astnode> line
%type <stmt> stmt defm


%token EOL ENDSTMT PRINT FACT ABS POT DEF 
%token <i> NUM
%token <id> ID
%token EQ LE GE NE L G
%token IF IFE THEN ELSE
%token WHILE DO FOR IN FOREACH
%token AND OR NOT
%token <s> STRING

%start line

%nonassoc '=' 
%left NOT AND OR
%left EQ NE L LE G GE
%left '+' '-' 
%left '*' '/' 


%%

line  : stmt             { a = $$ = st_par($1 , NULL); }
      | defm             { a = $$ = st_par($1 , NULL); }
      | stmt EOL line    { a = $$ = st_par($1 , $3);   }
      | EOL line         { a = $$ = st_par(NULL , $2); }
      |                  { a = $$ = NULL;              }
      ;
         
stmt : expr                                                                     { $$ = s_expr($1);                                }
     | IFE     {get_id_both("START");} cmpr THEN EOL slst ELSE EOL slst ENDSTMT { $$ = s_if($3, $6, $9);      get_id_both("END"); }
     | IF      {get_id_both("START");} cmpr THEN EOL slst ENDSTMT               { $$ = s_if($3, $6, NULL);    get_id_both("END"); }
     | WHILE   {get_id_both("START");} cmpr DO EOL slst ENDSTMT                 { $$ = s_while($3, $6);       get_id_both("END"); }
     | FOR     {get_id_both("START");} atrb ':' cmpr ':' atrb EOL slst ENDSTMT  { $$ = s_for($3, $5, $7, $9); get_id_both("END"); }
     | FOREACH {get_id_both("START");} vari IN ID EOL slst ENDSTMT              { $$ = s_pfor($3, $5, $7);    get_id_both("END"); }
     ;


defm : DEF {get_id_both("START");} ID '('args')' EOL slst ENDSTMT               { $$ = s_def($3 , $5 , $8); get_id_both("END"); }
     ;

args : ID                    { $$ = e_args_last($1);                 }
     | ID ',' args           { $$ = e_args($1 , $3);                 }
     ; 

slst :                       { $$ = NULL;                            }
     | stmt                  { $$ = sl_par($1 , NULL);               }
     | stmt EOL slst         { $$ = sl_par($1 , $3);                 }
     | EOL slst              { $$ = sl_par(NULL , $2);               }
     ;        

expr : ID '=' arit           { $$ = e_assign($1, $3);                }
     | ID '=' strn           { $$ = e_assign_string($1, $3);         }
     | ID'['NUM']'           { $$ = e_assign_array_num($1 , $3);     }
     | ID'['NUM']' '=' arit  { $$ = e_array_value_num($1 , $3 , $6); }
     | ID'['ID']' '=' arit   { $$ = e_array_value_str($1 , $3 , $6); }
     | ptrn                  { $$ = e_expr($1);                      }
     ;

atrb : ID '=' arit           { $$ = e_assign($1, $3); }
     ;

ptrn : PRINT'('arit')'       { $$ = e_print_arit($3);                }
     | PRINT'('STRING')'     { $$ = e_print_string($3);              }
     ;

strn : STRING                { $$ = e_string($1);                    }
     ;

vari : ID                    { $$ = e_id_pfor($1); }
     
arit : NUM                   { $$ = e_num($1);                       }
     | ID                    { $$ = e_id($1);                        }
     | ID'['NUM']'           { $$ = e_assign_array_num_find($1, $3); }
     | ID'['ID']'            { $$ = e_assign_array_str_find($1, $3); }
     | oper                  { $$ = e_expr($1);                      }
     | func                  { $$ = e_expr($1);                      }
     | cmpr                  { $$ = e_expr($1);                      }
     ; 

func : ABS'('arit')'         { $$ = e_abs($3);                       } 
     | POT'('arit','arit')'  { $$ = e_pot($3, $5);                   } 
     | FACT'('arit')'        { $$ = e_fact($3);                      } 
     ;       

cmpr : arit EQ arit          { $$ = e_equal($1 , $3);                }
     | arit NE arit          { $$ = e_notequal($1 , $3);             }
     | arit L arit           { $$ = e_less($1 , $3);                 }
     | arit LE arit          { $$ = e_lessequal($1 , $3);            }
     | arit G arit           { $$ = e_greater($1 , $3);              }
     | arit GE arit          { $$ = e_greaterequal($1 , $3);         }
     | arit AND arit         { $$ = e_and($1 , $3);                  }
     | arit OR arit          { $$ = e_or($1 , $3);                   }
     | NOT arit              { $$ = e_not($2);                       }
     | '(' arit ')'          { $$ = $2;                              }
     ;        

oper : arit '+' arit         { $$ = e_mais($1 , $3);                 }
     | arit '-' arit         { $$ = e_menos($1 , $3);                }
     | arit '*' arit         { $$ = e_vezes($1 , $3);                }
     | arit '/' arit         { $$ = e_div($1 , $3);                  }
     | arit '%' arit         { $$ = e_mod($1 , $3);                  }
     ;

%%


int main (int argc, char **argv) {
  hash_table = create_table(11);
  item_rpst = create_item_repository();
  item_rpst_find = create_item_repository();
  int value = yyparse();
  print_el(a);
}
