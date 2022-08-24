#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *key;
  int  value;
} arg;

struct scope {
  char * type;
  arg args[100];
  int value;
  struct scope * scopes[100];
  int return_value;
};

void changestruct(struct scope * a) {
  a->type = "marcell";
}

void c2(int a[100]) {
  a[0] = 99;
}

arg find_iden(char * str, arg * args, int argscount) {
  int i = 0;
  arg result;
  int didfind = 0;
  while(i < argscount) {
    if(strcmp(args[i].key, str) == 0) {
      result = args[i];
      didfind = 1;
      break;
    }
  }
  if(didfind == 0) {
    printf("ERROR: could not find arg: %s\n", str);
    exit(1);
  }
  return result;
}

int main() {
  arg a = {
    .key = "n", 
    .value = 2
  };
  if(a.value > 0) {
    printf("bigger than zero\n");
  }
  //printf("result: %d\n", result);
}
