%{

#include <stdio.h>
#include <string.h>
#include "square.tab.h"
void showError();
%}


numbers     ([0-9])+
operation   ([+])+
print       (\:print)
op_bra      ([\[])
cl_bra      ([\]])
idfunc      (\:[a-z]+)
identifier  ([a-z]+)
nline       (\n)
equal       ([=])


%%

{numbers}      { yylval.number = atoi(yytext); return (NUM);}
{operation}    { yylval.string = strdup(yytext); return (OP);}
{print}        { return (PRINT);}
{op_bra} { 
  yylval.string = strdup(yytext); 
  return (OPBRA);
}
{cl_bra} { 
  yylval.string = strdup(yytext); 
  return (CLBRA);
}
; { return (SEMICOLUMN); } 
, { return (COM); } 
: { return (COL); } 
> { 
  yylval.string = strdup(yytext); 
  return (GT); 
}
< { 
  yylval.string = strdup(yytext); 
  return (LT); 
}
{idfunc} { 
  yylval.string = strdup(yytext); 
  return (IDFUNC); 
}
{identifier} {
  yylval.string = strdup(yytext); 
  return (ID); 
}
{nline} { return (NLINE); }
{equal} { return (EQ); }

%%


void showError(){
  printf("Other input");
}
