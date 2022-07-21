#include <stdio.h>
#include <string.h>
#include "exec.h"

int traverse(struct scope * node) {
  printf("node type: %s\n", node->type);
  if(strcmp(node->type, "number") == 0) {
    return node->value;
  }
  if(node->scopescount > 0) {
    int i = 0;
    while(i < node->scopescount) {
      int result = traverse(node->scopes[i]);
      // check if it is the last value of the array
      if(i == (node->scopescount - 1)) {
        node->return_value = result;
      }
      i++;
    }
  }
  return node->return_value;
}

void exec(struct scope * global) {
  traverse(global);
}
