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



int main() {
  struct scope scopes[2] = {
    { 
      .type = "testing"
    }, 
    {
      .type = "ok",
      .scopes = {
        &((struct scope){
          .type = "if"
        })
      }
    }
  };
  printf("%s\n", scopes[1].scopes[0]->type);
}
