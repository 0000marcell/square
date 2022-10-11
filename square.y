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
  int didfind = 0;
  struct scope * tmp = sc;
  while(tmp != NULL) {
    if(strcmp(tmp->type, "body") == 0) {
      didfind = 1;
      break;
    }
    tmp = tmp->next;
  }
  if(didfind == 0) {
    printf("ERROR: could not find body on scope %s\n", sc->type);
    exit(1);
  }
  return tmp;
}

void set_body_next_address(struct scope * sc, struct scope * sc2) {
  struct scope * body = find_body(sc->scopes);
  if(body->scopes == NULL) {
    body->scopes = sc2;
    return;
  }
  struct scope * tmp = body->scopes;
  while(tmp != NULL) {
    if(tmp->next == NULL) {
      tmp->next = sc2;
      break;
    }
    tmp = tmp->next;
  };
}

struct scope global = {
  .type = "function",
  .extra = "global",
  .return_value = 0,
  .args = &(struct arg) {
  },
  .scopes = &(struct scope) {
    .type = "body",
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
%type <string> EQ
%type <string> ID 
%type <string> ifcomp 
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
      struct scope * ass = (struct scope *) malloc(sizeof(struct scope));
      (ass)->type = "assignment";
      struct scope * iden = (struct scope *) malloc(sizeof(struct scope));
      (iden)->type = "iden";
      (iden)->extra = $1;
      struct scope * number = (struct scope *) malloc(sizeof(struct scope));
      (number)->type = "number";
      (number)->value = $3;
      (ass)->scopes = iden;
      (ass)->scopes->next = number;
      set_body_next_address(cscope, ass);
    }
    | OPBRA IDFUNC ID ifcomp NUM COL {
      struct scope * sif = (struct scope *) malloc(sizeof(struct scope));
      (sif)->type = "if";
      struct scope * ifbody = (struct scope *) malloc(sizeof(struct scope));
      (ifbody)->type = "body";
      struct scope * iden = (struct scope *) malloc(sizeof(struct scope));
      (iden)->type = "iden";
      (iden)->extra = $3;
      struct scope * number = (struct scope *) malloc(sizeof(struct scope));
      (number)->type = "number";
      (number)->value = $5;
      struct scope * comp = (struct scope *) malloc(sizeof(struct scope));
      (comp)->type = "comp";
      if(strcmp($4, "=") == 0) {
        (comp)->extra = "==";
      } else {
        (comp)->extra = $4;
      }
      (comp)->scopes = iden; 
      (comp)->scopes->next = number;
      (sif)->scopes = comp;
      (sif)->scopes->next = ifbody;
      set_body_next_address(cscope, sif);
      prevscope = cscope;
      cscope = sif;
    }
    | OPBRA GT IDFUNC ID COL {
      struct scope * func = (struct scope *) malloc(sizeof(struct scope));
      (func)->type = "function";
      (func)->extra = $2;
    }  
    | CLBRA NLINE {
      cscope = prevscope;
      printf("the end!!!");
    }
    | NLINE {
      //do nothing!!!
    }
;

ifcomp: LT | GT | EQ EQ
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
    printf("before exec\n");
    exec(&global);
    printf("after exec\n");
    return 0;
}

