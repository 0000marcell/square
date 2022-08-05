#include <stdio.h>
#include <string.h>
#include "exec.h"

int find_iden(char * str, arg * args, int argscount) {
  int i = 0;
  int result;
  int didfind = 0;
  while(i < argscount) {
    if(strcmp(args[i].key, str) == 0) {
      result = args[i].value;
      didfind = 1;
      break;
    }
  }
  if(didfind == 0) {
    printf("ERROR: could not find arg: %s\n", str);
  }
  return result;
}

int traverse(struct scope * node, arg * args, int argscount) {
  printf("node type: %s\n", node->type);
  if(strcmp(node->type, "number") == 0) {
    return node->value;
  }
  if(node->scopescount > 0) {
    int i = 0;
    while(i < node->scopescount) {
      int result;
      if(strcmp(node->type, "if") == 0) {
        printf("enter if!!!\n");
        struct scope * comp = node->scopes[0];
        struct scope * body = node->scopes[1];
        i++;
        if(strcmp(comp->extra, "<") == 0) {
          int v1;
          int v2;
          if(strcmp(comp->scopes[0]->type, "iden") == 0) {
            v1 = find_iden(comp->scopes[0]->extra,args, argscount);
          } else {
            v1 = comp->scopes[0]->value;
          }
          if(strcmp(comp->scopes[1]->type, "iden") == 0) {
            v2 = find_iden(comp->scopes[1]->extra,args, argscount);
          } else {
            v2 = comp->scopes[1]->value;
          }
          if(v1 < v2) {
            result = traverse(body, args, argscount);
          }
        }
      } else {
        result = traverse(node->scopes[i], args, argscount);
      }
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
  traverse(global, global->args, global->argscount);
}
