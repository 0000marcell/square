%{
#include <stdio.h>

#define YYDEBUG 1 // This is new

extern FILE *yyin;
int yylex();
int yyerror(char *s);
int result = 0;
char operation = '+';
%}

%token NUM OP SEMICOLUMN PRINT OPBRA CLBRA OTHER

%type <number> NUM
%type <character> OP 
%type	<number> stmt

%union{
    int number;
    char character;
}

%%

prog: fcall fcall 
;

stmts: 
     | stmt OP stmts  
     | stmt stmts

stmt: 
    NUM { 
      printf("this is the number;\n");
      if(operation == '+') {
        result = result + $1; 
      }
    } 
    | SEMICOLUMN { 
      printf("%d\n", result); 
      result = 0;
    }

fcall: PRINT { 
        printf("print!!!\n"); 
     }

bra: OPBRA {
    printf("OPBRA\n");
   }
   | CLBRA {
    printf("CLBRA\n");
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

