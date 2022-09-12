%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./exec.h"

#define YYDEBUG 1 // This is new

extern FILE *yyin;
int yylex();
int yyerror(char *s);

struct scope global = {
  .type = "function",
  .extra = "global",
  .return_value = 0,
  .argscount = 1,
  .scopescount = 1,
  .scopes = {
    &(struct scope) {
      .type = "body"
    }
  }
};

struct scope * OPEN_BODY;
int IS_BODY_OPEN = 0;

%}

%token NUM OP SEMICOLUMN PRINT OPBRA CLBRA IDFUNC GT LT OTHER ID COM COL NLINE EQ

%type <number> NUM
%type <string> IDFUNC 
%type <string> OPBRA 
%type <string> CLBRA 
%type <string> GT 
%type <string> LT 
%type <string> ID 
%type <string> OP 
%type	<number> stmt

%union{
    int number;
    char *string;
}

%%

prog: stmts 
;

stmts: 
     | stmt stmts 

stmt: ID EQ NUM {
      if(IS_BODY_OPEN) {
        BODY
      } else {
      }
      farg = find_iden($1, global.args[0], global.argscount);
      farg.value = $3;
      /* global.args[0].key = $1; */  
      /* global.args[0].value = $3; */  
      printf("after!");
    } 
    | OPBRA IDFUNC ID LT NUM COL {
      global.scopescount++;
      if(strcmp($2, "if") == 0) {
        struct scope sc = {
          .type = "if",
          .scopescount = 2,
          .scopes = {
            &(struct scope) {
              .type = "comp",
              .extra = "<",
              .scopescount = 2,
              .scopes = {
                &(struct scope) {
                  .type = "iden",
                  .extra = $3
                },
                &(struct scope) {
                  .type = "number",
                  .value = $5
                },
              }
            }
          }
        };
        OPEN_BODY = sc.scopes[1];
        IS_BODY_OPEN = 1;
        global.scopes[0] = &sc;
      }
    }
    | NLINE {
      //do nothing!!!
    }
;


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
      printf("File does not exist!!!");
      return -1;
    }
    yyin = pt;
    do
    {
      yyparse();
    }while (!feof(yyin));
    return 0;
}

