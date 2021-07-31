%{

#include "ast.h"
#include "calc.tab.h"
#include <string.h>

%}

%%

true {yylval.i = 1 ; return NUM;}
false {yylval.i = 0 ; return NUM;}


"["         return '[';
"]"         return ']';
"("		    return '(';
")"		    return ')';
"+"		    return '+';
"-"		    return '-';
"*"		    return '*';
"/"		    return '/';
"%"         return '%';
"="         return '=';

"=="        return EQ;
"!="        return NE;
"<"         return L;
"<="        return LE;
">"         return G;
">="        return GE;

if          return IF;
ife         return IFE;
then        return THEN;
else        return ELSE;
while       return WHILE;
for         return FOR;
foreach     return FOREACH;
do          return DO;
in          return IN;
"{"         return '{';
"}"         return '}';
":"         return ':';
","         return ',';

and         return AND;
"&&"        return AND;
or          return OR;
"||"        return OR;
not         return NOT;
'!'         return NOT;

print       return PRINT;
abs         return ABS;
pot         return POT;
fact        return FACT;
def         return DEF;


[-]?[0-9]+		       { yylval.i = atoi(yytext); return NUM;       }
 
[a-zA-Z_]+[0-9]*       { yylval.id = strdup(yytext); return ID;     }

["][a-zA-Z_]+[0-9]*["] { yylval.s = strdup(yytext); return STRING;  }


;		    return ENDSTMT;
\n		    return EOL;

[ \t]+		{}

%%
