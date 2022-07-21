#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../exec.h"

int main() {
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
  struct scope ifst;
  ifst.type = "if";
  ifst.value = 1;
  struct scope nst; 
  nst.type = "number";
  nst.value = 99;
  ifst.scopes[0] = &nst;
  fibfunc.scopes[0] = &ifst;
  exec(global);
  printf(">>>>> return_value %d\n", global.scopes[0]->return_value);
  assert(global.scopes[0]->return_value == 99);
  return 0;
}
