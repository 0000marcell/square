%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYDEBUG 1 // This is new

extern FILE *yyin;
int yylex();
int yyerror(char *s);

int is_body_open = 0;

typedef struct {
  char *key;
  char *value;
  char *args[100];
} statement;

typedef struct {
  char *key;
  int  value;
} arg;

typedef struct {
  int id;
  char *key;
  int argssize;
  arg args[100];
  int bodysize;
  func body[100];
  int return_value;
} func;

func global = {
  .key = "global",
  .argssize = 0,
  .bodysize = 0,
}

func findfunc(char *key) {
  int res = -1;
  bodysize = global.bodysize;
  for(int i = 0; i <= bodysize; i++) {
    if(strcmp(global.body[i].key, key) == 0) {
      res = i;
      break;    
    }
  }
  if(res == -1) {
    printf("could not find func: %s \n", key);
    exit(1);
  }
  return funcarr[res];
}

arg findargs(func f, char *key) {
  int asize = f.argssize;
  int res = -1;
  for(int i = 0; i < asize; i++) {
    if(strcmp(f.args[i].key, key) == 0) {
      res = i;
      break;    
    }
  } 
  if(res == -1) {
    printf("could not find arg: %s \n", key);
    exit(1);
  }
  return f.args[res];
}

%}

%token NUM OP SEMICOLUMN PRINT OPBRA CLBRA IDFUNC GT OTHER ID COM COL NLINE EQ

%type <number> NUM
%type <string> IDFUNC 
%type <string> OPBRA 
%type <string> CLBRA 
%type <string> GT 
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

stmt: OPBRA GT IDFUNC {
      funcarr[funccount].key = $3;
      funcarr[funccount].id = funccount;
      is_body_open = 1;
    }
    | ID COM ID COL NLINE {
      arg arg0 = {
        .key = $1
      };
      arg arg1 = {
        .key = $3
      };
      funcarr[funccount].args[0] = arg0;
      funcarr[funccount].args[1] = arg1;
      funcarr[funccount].argssize = 2;
    }
    | NLINE CLBRA NLINE {
      printf(">>>>>>>> closing function\n");
      is_body_open = 0;
      funccount++;
    }
    | OPBRA IDFUNC NUM COM NUM CLBRA {
      printf("executing the function!!!");
      printf("%d %d\n", $3, $5);
      func function = findfunc($2);
      function.args[0].value = $3;
      function.args[1].value = $5;
      char *bkey = function.body[0].key;
      char *bval = function.body[0].value;

      if(strcmp(bkey, "operation") == 0) {
        if(strcmp(bval, "+") == 0) {
          arg a = findargs(function, function.body[0].args[0]);
          arg b = findargs(function, function.body[0].args[1]);
          int v1 = a.value;
          int v2 = b.value;
          int result = v1 + v2;
          printf(">>>>>> %d\n", result);
          function.return_value = result;
        }
      }
    } 
    | OPBRA PRINT NUM CLBRA {
      printf(">>> %d\n", $3);
    }
    | ID EQ NUM {
      if(is_body_open == 1) {
      } else {
        funcarr[funccount].key = "global";
        funcarr[funccount].id = funccount;
        funcarr[funccount].id = funccount;
      }
    }
    | ID OP ID {
      statement st = {
        .key = "operation",
        .value = $2
      };
      st.args[0] = $1;
      st.args[1] = $3;
      printf(">>>>>> %s\n", st.args[0]);
      if(is_body_open == 1) {
        funcarr[funccount].body[0] = st;
      }
    } 
    | NLINE {
      printf("do nothing!!!\n");
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

