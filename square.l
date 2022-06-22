%{

#include <stdio.h>
#include <string.h>
#include "calc.tab.h"
void showError();
%}


numbers     ([0-9])+
operation   ([+])+
print       (\:print)
op_bra      ([\[])
cl_bra      ([\]])

%%

{numbers}      {yylval.number = atoi(yytext); return (NUM);}
{operation}    {return (OP);}
{print}        {return (PRINT);}
{op_bra}       {return (OPBRA);}
{cl_bra}       {return (CLBRA);}
;              {return (SEMICOLUMN); } 

%%


void showError(){
  printf("Other input");
}
