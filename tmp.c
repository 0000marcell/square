#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#

typedef struct {
  char *key;
  int  value;
} arg;

struct scope {
  char * type;
  char * extra;
  int argscount;
  arg args[100];
  int value;
  int scopescount;
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

void func(int n, int abort) {
  printf("func!\n");
}

struct scope global = {
  .type = "function",
  .extra = "global",
  .return_value = 0,
  .scopescount = 3,
  .scopes = {
    &(struct scope) {
      .type = "body"
    }
  }
};


int main() {

  struct scope * body = global.scopes[0];

  int i = 0;
  
  while(i < 2) {
    struct scope *sc1 = (struct scope *) malloc(sizeof(struct scope));
    (sc1)->type = "if";
    body->scopes[i] = sc1; 
    struct scope *sc2 = (struct scope *) malloc(sizeof(struct scope));
    (sc2)->argscount = i;
    body->scopes[i]->scopes[0] = sc2; 
    printf("before argscount: %d\n", body->scopes[i]->scopes[0]->argscount);
    printf("address: %p\n", &body->scopes[i]);
    i++;
  }
  printf("after argscount: %d\n", body->scopes[0]->scopes[0]->argscount);
  printf("after argscount: %d\n", body->scopes[1]->scopes[0]->argscount);
  printf("address : %p\n", &body->scopes[0]);
  printf("address : %p\n", &body->scopes[1]);
  return 0;
}
