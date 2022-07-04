%{
#include <stdio.h>

#define YYDEBUG 1 // This is new

extern FILE *yyin;
int yylex();
int yyerror(char *s);
int result = 0;
char operation = '+';
typedef struct {
  char *key;
  char *value;
} arg;

typedef struct {
  char *key;
  arg *args[100];
  char *body;
} func;

func funcarr[100] = {};

int funccount = 0;
%}

%token NUM OP SEMICOLUMN PRINT OPBRA CLBRA IDFUNC GT OTHER ID COM COL NLINE

%type <number> NUM
%type <string> IDFUNC 
%type <string> OPBRA 
%type <string> CLBRA 
%type <string> GT 
%type <string> ID 
%type <character> OP 
%type	<number> stmt

%union{
    int number;
    char character;
    char *string;
}

%%

prog: stmts 
;

stmts: 
     | stmt stmts 

stmt: OPBRA GT IDFUNC {
      printf("3: %s\n", $3);
      funcarr[funccount].key = $3;
    }
    | ID COM ID COL {
      arg arg0 = {
        .key = $1
      };
      arg arg1 = {
        .key = $3
      };
      funcarr[funccount].args[0] = &arg0;
      funcarr[funccount].args[1] = &arg1;
      printf("arg1: %s, arg2: %s\n", funcarr[funccount].args[0]->key, funcarr[funccount].args[1]->key);
    }
    | NLINE BODY NLINE CLBRA {
      printf("NEWLINE!\n");
    }
;
/* stmts: OPBRA GT IDFUNC { */
/*        funcarr[funccount].key = $3; */          
/*        printf("idfunc: %s\n", funcarr[funccount].key); */
/*      } */ 
/*      | ID COM ID COL { */
/*        /1* funcarr[funccount].args[0]->key = $1; *1/ */
/*        /1* funcarr[funccount].args[1]->key = $3; *1/ */
/*        printf("1: %s, 3: %s \n", $1, $3); */
/*        //printf("arg1: %s, arg2: %s ", funcarr[funccount].args[0]->key, funcarr[funccount].args[1]->key); */
/*      } */

/* stmt: */ 
/*     NUM { */ 
/*       printf("this is the number;\n"); */
/*       if(operation == '+') { */
/*         result = result + $1; */ 
/*       } */
/*     } */ 
/*     | SEMICOLUMN { */ 
/*       printf("%d\n", result); */ 
/*       result = 0; */
/*     } */

/* fcall: PRINT */
/*      | IDFUNC */

/* bra: OPBRA | CLBRA */

%%

int yyerror(char *s)
{
	printf("Syntax Error on line %s\n", s);
	return 0;
}

int main() {
    yydebug = 1;
    FILE * pt = fopen("source.sq", "r" );
    if(!pt) {
      printf("File doesn not exist!!!");
      return -1;
    }
    yyin = pt;
    do
    {
      yyparse();
    }while (!feof(yyin));
    return 0;
}

