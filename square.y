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

int IS_IDEN = 0;

struct scope * cscope = &global;
struct scope * prevscope = &global;
struct scope * cargs = &global;
struct scope * prevargs = &global;

// finds the key of a argument function
char * find_func_args(int pos, char * fname) {
  int didfind = 0;
  struct scope * tmp = global.scopes->scopes;
  char * result;
  while(tmp != NULL) {
    if(strcmp(tmp->type, "function") == 0 &&
       strcmp(tmp->extra, fname) == 0) {

      struct arg * atmp = tmp->args;      
      int count = 1;
      while(atmp != NULL) {
        if(pos == count) {
          result = atmp->key;
          didfind = 1;
          break;
        }
        atmp = atmp->next;
        pos++;
      }
    }
    tmp = tmp->next;
  }
  if(didfind == 0) {
    printf("ERROR: could not argument key on function definition %s\n", fname);
    exit(1);
  }
  return result;
}

;

%}

%token NUM OP SEMICOLUMN PRINT RETURN OPBRA CLBRA IDFUNC GT LT OTHER ID COM COL NLINE EQ

%union{
  int number;
  char *string;
  union StringNumber {
    int i;
    char *s;
  } strnum;
  struct scope * node;
}

%type <number> NUM
%type <string> IDFUNC 
%type <string> OPBRA 
%type <string> CLBRA 
%type <string> GT 
%type <string> LT 
%type <string> EQ
%type <string> ID 
%type <string> ifcomp 
%type <node> binop 
%type <node> fcall 
%type <strnum> param 
%type <string> OP 
%type	<number> stmt

%%

prog: stmts 
;

stmts: 
     | stmt stmts 

stmt: ID EQ NUM {
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
    | RETURN fcall {
      struct scope * rreturn = (struct scope *) malloc(sizeof(struct scope));
      (rreturn)->type = "return";

      struct scope * return_body = (struct scope *) malloc(sizeof(struct scope));
      (return_body)->type = "body";
      
      struct scope * ass1 = (struct scope *) malloc(sizeof(struct scope));
      (ass1)->type = "assignment";

      struct scope * iden1 = (struct scope *) malloc(sizeof(struct scope));
      (iden1)->type = "iden";
      (iden1)->extra = "n";

      struct scope * ass2 = (struct scope *) malloc(sizeof(struct scope));
      (ass2)->type = "assignment";

      struct scope * iden2 = (struct scope *) malloc(sizeof(struct scope));
      (iden2)->type = "iden";
      (iden2)->extra = $2->args->key;

      (rreturn)->scopes = return_body;
      (return_body)->scopes = ass1;
      (ass1)->scopes = iden1;
      (iden1)->next = $2;
      
      (ass2)->scopes = iden2;
      (iden2)->next = $4;
      
      set_body_next_address(cscope, rreturn);
    }
    | RETURN OPBRA IDFUNC ID CLBRA OP OPBRA IDFUNC ID CLBRA {
      struct scope * rreturn = (struct scope *) malloc(sizeof(struct scope));
      (rreturn)->type = "return";

      struct scope * return_body = (struct scope *) malloc(sizeof(struct scope));
      (return_body)->type = "body";

      struct scope * bin_op = (struct scope *) malloc(sizeof(struct scope));
      (bin_op)->type = "binary_op";
      (bin_op)->extra = $6;

      struct scope * fcall1 = (struct scope *) malloc(sizeof(struct scope));
      (fcall1)->type = "fcall";
      (fcall1)->extra = $3;
      (fcall1)->extra++;
      struct arg * fcall_args1 = (struct arg *) malloc(sizeof(struct arg));
      (fcall_args1)->key = $4;
      (fcall1)->args = fcall_args1;

      struct scope * fcall2 = (struct scope *) malloc(sizeof(struct scope));
      (fcall2)->type = "fcall";
      (fcall2)->extra = $8;
      (fcall2)->extra++;
      struct arg * fcall_args2 = (struct arg *) malloc(sizeof(struct arg));
      (fcall_args2)->key = $9;
      (fcall2)->args = fcall_args2;

      (rreturn)->scopes = return_body;
      (return_body)->scopes = bin_op;
      (bin_op)->scopes = fcall1;
      (fcall1)->next = fcall2;
      set_body_next_address(cscope, rreturn);
    }
    | RETURN OPBRA IDFUNC binop CLBRA OP OPBRA IDFUNC binop CLBRA {
      struct scope * rreturn = (struct scope *) malloc(sizeof(struct scope));
      (rreturn)->type = "return";

      struct scope * return_body = (struct scope *) malloc(sizeof(struct scope));
      (return_body)->type = "body";

      struct scope * bin_op_fcall = (struct scope *) malloc(sizeof(struct scope));
      (bin_op_fcall)->type = "binary_op";
      (bin_op_fcall)->extra = $6; 

      // fcall1
      struct scope * fcall1 = (struct scope *) malloc(sizeof(struct scope));
      (fcall1)->type = "fcall";
      (fcall1)->extra = $3;
      (fcall1)->extra++;

      struct arg * fcall1_args = (struct arg *) malloc(sizeof(struct arg));
      (fcall1_args)->key = $4->scopes->extra;

      struct scope * fcall1_ass = (struct scope *) malloc(sizeof(struct scope));
      (fcall1_ass)->type = "assignment";

      struct scope * fcall1_ass_iden1 = (struct scope *) malloc(sizeof(struct scope));
      (fcall1_ass_iden1)->type = "iden";
      (fcall1_ass_iden1)->extra = $4->scopes->extra;

      (fcall1)->args = fcall1_args;
      (fcall1)->scopes = fcall1_ass;
      (fcall1_ass)->scopes = fcall1_ass_iden1;
      (fcall1_ass)->scopes->next = $4;

      // fcall2
      struct scope * fcall2 = (struct scope *) malloc(sizeof(struct scope));
      (fcall2)->type = "fcall";
      (fcall2)->extra = $8;
      (fcall2)->extra++;

      struct arg * fcall2_args = (struct arg *) malloc(sizeof(struct arg));
      (fcall2_args)->key = $9->scopes->extra;

      struct scope * fcall2_ass = (struct scope *) malloc(sizeof(struct scope));
      (fcall2_ass)->type = "assignment";

      struct scope * fcall2_ass_iden1 = (struct scope *) malloc(sizeof(struct scope));
      (fcall2_ass_iden1)->type = "iden";
      (fcall2_ass_iden1)->extra = $9->scopes->extra;

      (fcall2)->args = fcall2_args;
      (fcall2)->scopes = fcall2_ass;
      (fcall2_ass)->scopes = fcall2_ass_iden1;
      (fcall2_ass)->scopes->next = $9;

      (rreturn)->scopes = return_body;
      (return_body)->scopes = bin_op_fcall;
      (bin_op_fcall)->scopes = fcall1;
      (bin_op_fcall)->scopes->next = fcall2;
      set_body_next_address(cscope, rreturn);
    }
    | ID EQ OPBRA IDFUNC NUM CLBRA {
      struct scope * ass = (struct scope *) malloc(sizeof(struct scope));
      (ass)->type = "assignment";
      struct scope * iden = (struct scope *) malloc(sizeof(struct scope));
      (iden)->type = "iden";
      (iden)->extra = $1;
      (ass)->scopes = iden;
      struct scope * fcall = (struct scope *) malloc(sizeof(struct scope));
      (fcall)->type = "fcall";
      (fcall)->extra = $4;
      (fcall)->extra++;
      (iden)->next = fcall;
      struct arg * farg = (struct arg *) malloc(sizeof(struct arg));

      (farg)->key = find_func_args(1, (fcall)->extra);
      (farg)->skip_update = 1;
      (farg)->value = $5;
      (fcall)->args = farg;
      set_body_next_address(cscope, ass);
    }
    | OPBRA PRINT param CLBRA {
      struct scope * print = (struct scope *) malloc(sizeof(struct scope));
      (print)->type = "print";
      struct scope * pscope = (struct scope *) malloc(sizeof(struct scope));
      if(IS_IDEN) {
        (pscope)->type = "iden";
        (pscope)->extra = $3.s;
      } else {
        (pscope)->type = "number";
        (pscope)->value = $3.i;
      }
      (print)->scopes = pscope;
      set_body_next_address(cscope, print);
    }
    | RETURN binop {
      struct scope * rreturn = (struct scope *) malloc(sizeof(struct scope)); 
      (rreturn)->type = "return";
      struct scope * body = (struct scope *) malloc(sizeof(struct scope)); 
      (body)->type = "body";

      struct scope * ass = (struct scope *) malloc(sizeof(struct scope)); 
      (ass)->type = "assignment";

      struct scope * iden = (struct scope *) malloc(sizeof(struct scope)); 
      (iden)->type = "iden";
      (iden)->extra = $2->scopes->extra;

      (rreturn)->scopes = body; 
      (body)->scopes = ass;
      (ass)->scopes = iden; 
      (iden)->next = $2;
      set_body_next_address(cscope, rreturn);
    } 
    | ID {
      struct scope * id = (struct scope *) malloc(sizeof(struct scope)); 
      (id)->type = "iden";
      (id)->extra = $1;
      set_body_next_address(cscope, id);
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
      sif->prev = cscope;
      cscope = sif;
    }
    | OPBRA GT IDFUNC ID COL {
      struct scope * func = (struct scope *) malloc(sizeof(struct scope));
      (func)->type = "function";
      (func)->extra = $3;
      (func)->extra++;
      struct arg * args = (struct arg *) malloc(sizeof(struct arg));
      (args)->key = $4;
      (func)->args = args; 
      struct scope * body = (struct scope *) malloc(sizeof(struct scope));
      (body)->type = "body";
      (func)->scopes = body; 
      set_body_next_address(cscope, func);
      func->prev = cscope;
      cscope = func;
      prevscope = cscope;
      cscope = func;
    }  
    | CLBRA NLINE {
      cscope = cscope->prev;
    }
    | NLINE {
      //do nothing!!!
    } 
;

ifcomp: LT | GT | EQ EQ
;

param: ID {
       IS_IDEN = 1;
     }
     | NUM {
       IS_IDEN = 0;
     }
;

fcall: OPBRA IDFUNC binop CLBRA {
       struct scope * fcall = (struct scope *) malloc(sizeof(struct scope));
       (fcall)->type = "fcall";
       (fcall)->extra = $2;
       (fcall)->extra++;
       struct arg * fcall_args = (struct arg *) malloc(sizeof(struct arg));
       (fcall_args)->key = $3->scopes->extra;
       (fcall)->args = fcall_args;

       struct scope * fcall_body = (struct scope *) malloc(sizeof(struct scope));
       (fcall_body)->type = "body";
       (fcall)->scopes = fcall_body;
       (fcall_body)->scopes = ass2;

       $$ = fcall;
     }

binop: ID OP NUM {
       struct scope * bin_op = (struct scope *) malloc(sizeof(struct scope));
       (bin_op)->type = "binary_op";
       (bin_op)->extra = $2;  

       struct scope * iden = (struct scope *) malloc(sizeof(struct scope));
       (iden)->type = "iden";
       (iden)->extra = $1;

       struct scope * num = (struct scope *) malloc(sizeof(struct scope));
       (num)->type = "number";
       (num)->value = $3;

       (bin_op)->scopes = iden;
       (iden)->next = num;

       $$ = bin_op;
     }
;




%%

int yyerror(char *s)
{
	printf("Syntax Error on line %s\n", s);
	return 0;
}

int main(int argc, char *argv[]) {
    yydebug = 0;
    FILE * pt = fopen(argv[1], "r" );
    if(!pt) {
      printf("File does not exist!!!");
      return -1;
    }
    yyin = pt;
    do
    {
      yyparse();
    }while (!feof(yyin));
    exec(&global);
    return 0;
}

