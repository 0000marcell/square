#include <stdio.h>

typedef struct {
  char *key;
  char *value;
} arg;

typedef struct {
  char *key;
  arg *args[100];
  char *body;
} func;

int main() {
  arg arg1 = {
    .key = "a" 
  };
  func item1 = {
    .key = "marcell"
  };
  item1.args[0] = &arg1;
  printf("%s\n", item1.args[0]->key);
}
