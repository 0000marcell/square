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
      .type = "body",
      .scopescount = 0
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
      printf("assignment!!!\n");
      struct scope first_structure = {
        .type = "assignment",
        .scopescount = 2,
      };
      struct scope iden = {
        .type = "iden",
        .extra = $1
      };
      struct scope number = {
        .type = "number",
        .value = $3
      };
      first_structure.scopes[0] = &iden;
      first_structure.scopes[1] = &number;
      //he cannot find the body because declaring the above structure changed if
      // using different scopes for everything didn't fix the problem, I don't know why 
      // hes using the same address when creating new structure
      struct scope * body = find_body(cscope);
      body->scopes[body->scopescount] = &first_structure;
      body->scopescount++;
      /* arg * farg; */
      /* if(cargs->argscount > 0) { */
      /*   farg = find_iden($1, cargs->args, cargs->argscount, 0); */
      /* } */
      /* if(!farg) { */
      /*   cargs->args[cargs->argscount].key = $1; */
      /*   cargs->argscount++; */
      /* } */
    }
    | OPBRA IDFUNC ID LT NUM COL {
      printf("if!!!\n");
      if(strcmp($2, ":if") == 0) {
        struct scope * body = find_body(cscope);
        struct scope second_structure = {
          .type = "if",
          .scopescount = 2,
        };
        struct scope comp = {
          .type = "comp",
          .extra = "<",
          .scopescount = 2,
        };
        struct scope c1 = {
          .type = "iden",
          .extra = $3
        };
        struct scope c2 = {
          .type = "number",
          .value = $5
        };
        comp.scopes[0] = &c1;
        comp.scopes[1] = &c2;
        struct scope ifbody = {
          .type = "body",
          .scopescount = 0
        };
        second_structure.scopes[0] = &comp;
        second_structure.scopes[1] = &ifbody;
        body->scopes[body->scopescount] = &second_structure;
        body->scopescount++;
        prevscope = cscope;
        cscope = &second_structure; 
      }
    }
    | CLBRA NLINE {
      cscope = prevscope;
      printf("the end!!!");
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

