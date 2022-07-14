#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char *key;
  int argssize;
  arg args[100];
  statement body[100];
  int return_value;
} func;

func funcarr[100] = {};

int funccount = 0;

func findfunc(char *key) {
  int res = -1;
  for(int i = 0; i <= funccount; i++) {

    if(strcmp(funcarr[i].key, key) == 0) {
      res = i;
      break;    
    }
  }
  if(res == -1) {
    printf("could not find func!!!\n");
    exit(1);
  }
  return funcarr[res];
}

arg findargs(func f, char *key) {
  int asize = f.argssize;
  int res;
  for(int i = 0; i < asize; i++) {
    if(strcmp(f.args[i].key,key) == 0) {
      res = i;
      break;    
    }
  } 
  return f.args[res];
}

int main() {

  func function = {
    .key = ":fib",
    .argssize = 2,
  };

  arg arg0 = {
    .key = "a"
  };

  arg arg1 = {
    .key = "b"
  };

  function.args[0] = arg0;
  function.args[1] = arg1;
  funcarr[0] = function;

  statement ss = {
    .key = "operation",
    .value = "+",
  };

  funcarr[0].body[0] = ss;

  printf("%s\n", funcarr[0].body[0].key);
}
