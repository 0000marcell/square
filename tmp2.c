#include <stdio.h>

typedef struct {
  int value;
} s;

int main(void) {
  int a = 7;
  int *p;
  p = &a;
  printf("%p\n", p);
}
