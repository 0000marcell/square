#include <stdio.h>
#include <string.h>
#include "exec.h"
#include <stdlib.h>


arg * find_iden(char * str, arg * args, int argscount) {
  int i = 0;
  arg * result;
  int didfind = 0;
  while(i < argscount) {
    if(strcmp(args[i].key, str) == 0) {
      result = &args[i];
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

struct scope * GLOBAL_SCOPE;

struct scope * find_func(char * fname) {
  int i = 0;
  struct scope * result;
  int didfind = 0;
  while(i < GLOBAL_SCOPE->scopescount) {
    if(strcmp(GLOBAL_SCOPE->scopes[i]->type, "function") == 0 &&
       strcmp(GLOBAL_SCOPE->scopes[i]->extra, fname) == 0) {
      result = GLOBAL_SCOPE->scopes[i];
      didfind = 1;
      break;
    }
    i++;
  }
  if(didfind == 0) {
    printf("ERROR: could not find function with name: %s\n", fname);
    exit(1);
  }
  return result;
}

void update_args(struct scope * fscope, struct scope * nscope) {
  int i = 0;
  while(i < fscope->argscount) {
    int j = 0;
    while(j < nscope->argscount) {
      if(strcmp(fscope->args[i].key, nscope->args[j].key) == 0) {
        fscope->args[i].key = nscope->args[j].key;
        fscope->args[i].value = nscope->args[j].value;
      }
      j++;
    }
    i++;
  }
}

int find_bin_op(struct scope * node, arg * args, int argscount) {
  int result;
  if(strcmp(node->type, "iden") == 0) {
    result = find_iden(node->extra, args, argscount)->value;
  } else {
    if(strcmp(node->type, "number") == 0) {
      result = node->value;
    } else {
      printf("ERROR: invalid binary_op item: %s\n", node->type);
      exit(1);
    }
  }
  return result;
}

int traverse(struct scope * node, arg * args, int argscount) {
  printf("node type: %s\n", node->type);
  if(strcmp(node->type, "iden") == 0) {
    return find_iden(node->extra, args, argscount)->value;
  }
  if(strcmp(node->type, "number") == 0) {
    return node->value;
  }
  if(strcmp(node->type, "fcall") == 0){
    struct scope * func = find_func(node->extra);
    update_args(func, node);
    // func->scopes[0] is always the body of the function
    node->return_value = traverse(func->scopes[0], func->args, func->argscount);
    return node->return_value;
  }
  if(node->scopescount > 0) {
    int i = 0;
    while(i < node->scopescount) {
      int result;
      // case if body
      if(strcmp(node->type, "body") == 0){
        result = traverse(node->scopes[i], args, argscount);
      }
      // case global function 
      if(strcmp(node->type, "function") == 0 &&
        strcmp(node->extra, "global") == 0) {
        result = traverse(node->scopes[i], args, argscount);
      }
      // case binary_op
      if(strcmp(node->type, "binary_op") == 0){
        int v1 = find_bin_op(node->scopes[0], args, argscount);    
        int v2 = find_bin_op(node->scopes[1], args, argscount);
        if(strcmp(node->extra, "+") == 0) {
          result = v1 + v2;
        }
      }
      // case fcall 
      if(strcmp(node->type, "fcall") == 0){
        struct scope * func = find_func(node->extra);
        update_args(func, node);
        // func->scopes[0] is always the body of the function
        result = traverse(func->scopes[0], func->args, func->argscount);
      }
      // case if
      if(strcmp(node->type, "if") == 0) {
        struct scope * comp = node->scopes[0];
        struct scope * body = node->scopes[1];
        if(strcmp(comp->extra, "<") == 0) {
          int v1;
          int v2;
          if(strcmp(comp->scopes[0]->type, "iden") == 0) {
            v1 = find_iden(comp->scopes[0]->extra,args, argscount)->value;
          } else {
            v1 = comp->scopes[0]->value;
          }
          if(strcmp(comp->scopes[1]->type, "iden") == 0) {
            v2 = find_iden(comp->scopes[1]->extra,args, argscount)->value;
          } else {
            v2 = comp->scopes[1]->value;
          }
          if(v1 < v2) {
            // exectuts the body
            result = traverse(body, args, argscount);
          }
        }
      }
      // case assignment
      if(strcmp(node->type, "assignment") == 0) {
        if(strcmp(node->scopes[0]->type, "iden") == 0) {
          arg * iden = find_iden(node->scopes[0]->extra, args, argscount); 

          if(strcmp(node->scopes[1]->type, "number") == 0) {
            iden->value =  node->scopes[1]->value;
          }

          if(strcmp(node->scopes[1]->type, "fcall") == 0) {
            struct scope * func = find_func(node->scopes[1]->extra);
            update_args(func, node->scopes[1]);
            // func->scopes[0] is always the body of the function
            result = traverse(func->scopes[0], func->args, func->argscount);
            iden->value = result;
          }

          if(strcmp(node->scopes[1]->type, "binary_op") == 0) {
            result = traverse(node->scopes[1], args, argscount);
            iden->value = result;
          }
        } else {
          printf("ERROR: assigning to a non identifier!\n");
          exit(1);
        }
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
  GLOBAL_SCOPE = global;
  traverse(global, global->args, global->argscount);
}
