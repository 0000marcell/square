%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./exec.h"

#define YYDEBUG 1 // This is new

extern FILE *yyin;
int yylex();
int yyerror(char *s);

struct scope * find_body(struct scope * sc) {
  int i = 0;
  int didfind = 0;
  struct scope * result;
  while(i < sc->scopescount) {
    if(strcmp(sc->scopes[i]->type, "body") == 0) {
      result = sc->scopes[i];
      didfind = 1;
    }
    i++;
  }
  if(didfind == 0) {
    printf("ERROR: could not body on scope %s\n", sc->type);
    exit(1);
  }
  return result;
}

struct scope global = {
  .type = "function",
  .extra = "global",
  .return_value = 0,
  .argscount = 0,
  .scopescount = 1,
  .scopes = {
    &(struct scope) {
      .type = "body"
    }
  }
};

struct scope * cscope = &global;
struct scope * prevscope = &global;
struct scope * cargs = &global;
struct scope * prevargs = &global;


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
      struct scope sc = {
        .type = "iden",
        .extra = $1
      };
      struct scope * body = find_body(cscope);
      body->scopes[body->scopescount] = &sc; 
      body->scopescount++;
      arg * farg;
      if(cargs->argscount > 0) {
        farg = find_iden($1, cargs->args, cargs->argscount);
        if(strcmp(farg->key, $1) == 0) {
          farg->value = $3;
        }
      }
      if(!farg) {
        cargs->args[cargs->argscount].key = $1;
        cargs->args[cargs->argscount].value = $3;
        cargs->argscount++;
      }
    }
    | OPBRA IDFUNC ID LT NUM COL {
      if(strcmp($2, ":if") == 0) {
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
        cscope->scopescount++;
        cscope->scopes[cscope->scopescount] = &sc;
        prevscope = cscope;
        cscope = &sc;
      }
    }
    | CLBRA NLINE {
      cscope = prevscope;
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

