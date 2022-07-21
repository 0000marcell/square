#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *key;
  char *value;
  char *args[100];
} statement;


int funccount = 0;

/* { */
/*   key: "global", */ 
/*   argssize: 1, */
/*   arg: [ */
/*     { */
/*       key: "a", */
/*       value: 1 */
/*     } */
/*   ], */
/*   body: [ */
/*     { */
/*       key: "if", */
/*       condition: 1, // this going to be evaluated at combile time */ 
/*       body: [ */
/*         { */
/*           { */
/*             key: ":print", */
/*             value: 99 */
/*           } */
/*         } */
/*       ] */
/*     } */
/*   ] */
/* } */

typedef struct {
  char *key;
  int  value;
} arg;

struct scope {
  char * type;
  arg args[100];
  int value;
  struct scope *scopes[100];
  int return_value;
};

int main() {
  struct scope global; 
  global.type = "global"; 
  struct scope fibfunc;
  fibfunc.type = "fib";
  arg arg1 = {
    .key = "n",
    .value = 10
  };
  fibfunc.args[0] = arg1;
  global.scopes[0] = &fibfunc;
  struct scope ifst;
  ifst.type = "if";
  ifst.value = 1;
  struct scope nst; 
  nst.type = "number";
  nst.value = 0;
  ifst.scopes[0] = &nst;
  fibfunc.scopes[0] = &ifst;
  printf("%s\n", ifst.type);
  /* a.data = 1; */
  /* a.data2 = 2; */
  /* struct scope b; */
  /* b.data = 99; */
  /* b.data2 = 88; */
  /* a.to_test[0] = &b; */
  /* printf("%d\n", a.to_test[0]->data); */
}
