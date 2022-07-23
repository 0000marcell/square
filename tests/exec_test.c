#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../exec.h"

void first_case() {
  // function with one if statement returning 99
  printf("running tests...\n");
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
  global.scopescount = 1;
  struct scope ifst;
  ifst.type = "if";
  ifst.value = 1;
  struct scope nst; 
  nst.type = "number";
  nst.value = 99;
  ifst.scopes[0] = &nst;
  ifst.scopescount = 1;
  fibfunc.scopes[0] = &ifst;
  fibfunc.scopescount = 1;
  exec(&global);
  printf(">>>>> return_value %d\n", global.scopes[0]->return_value);
  assert(global.scopes[0]->return_value == 99);
}

void second_case() {
  // function with one if statement returning 99
  printf("running tests...\n");
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
  global.scopescount = 1;
  struct scope ifst;
  ifst.type = "if";
  ifst.value = 0;
  struct scope nst; 
  nst.type = "number";
  nst.value = 88;
  ifst.scopes[0] = &nst;
  ifst.scopescount = 1;
  fibfunc.scopes[0] = &ifst;
  fibfunc.scopescount = 1;

  struct scope ifst2;
  ifst2.type = "if";
  ifst2.value = 1;
  struct scope nst2; 
  nst2.type = "number";
  nst2.value = 99;
  ifst2.scopes[0] = &nst2;
  fibfunc.scopes[1] = &ifst2;
  fibfunc.scopescount = 2;
  exec(&global);
  printf(">>>>> return_value %d\n", global.scopes[0]->return_value);
  assert(global.scopes[0]->return_value == 99);
}

int main() {
  // function with one if statement returning 99
  //first_case();

  // function with two if statements second one returning 99 first returning 0
  second_case();

  return 0;
}
