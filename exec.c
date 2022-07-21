#include <stdio.h>
#include "exec.h"

void traverse(struct scope * node) {
  if(node->scopescount > 0) {
    int i = 0;
    while(i < node->scopescount) {
      traverse(node->scopes[i]);
      i++;
    }
  }
}

void exec(struct scope global) {
  
  printf("%s\n", global.type);

}
