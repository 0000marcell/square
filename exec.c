#include <stdio.h>
#include <string.h>
#include "exec.h"
#include <stdlib.h>

struct scope * GLOBAL_SCOPE;
int EARLY_RETURN = 0;

struct arg * find_iden(char * str, struct arg * args, int abort) {
  int didfind = 0;
  struct arg * item = args;
  while(item != NULL) {
    if(strcmp(str, item->key) == 0) {
      didfind = 1;
      break;
    }
    item = item->next; 
  }
  if(didfind == 0 && abort == 1) {
    printf("ERROR: could not find arg: %s\n", str);
    exit(1);
  }
  return item;
}


struct scope * find_func(char * fname) {
  int didfind = 0;
  struct scope * item = GLOBAL_SCOPE->scopes;
  while(item != NULL) {
    if(strcmp(item->type, "function") == 0 &&
       strcmp(item->extra, fname) == 0) {
      didfind = 1;
      break;
    }
    item = item->next;
  }
  if(didfind == 0) {
    printf("ERROR: could not find function with name: %s\n", fname);
    exit(1);
  }
  return item;
}

void update_args(struct arg * fargs, struct arg * nargs) {
  struct arg * fitems = fargs;
  struct arg * nitems = nargs;
  while(fitems != NULL) {
    while(nitems != NULL) {
      if(strcmp(fitems->key, nitems->key) == 0) {
        if(fitems->skip_update != 1) {
          fitems->value = nitems->value;
        }
      }
      nitems = nitems->next;
    }
    fitems = fitems->next;
  }
}

int find_bin_op(struct scope * node, struct arg * args) {
  int result;
  if(strcmp(node->type, "iden") == 0) {
    result = find_iden(node->extra, args, 1)->value;
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

int traverse(struct scope * node, struct arg * args) {
  printf("node type: %s\n", node->type);
  int result;
  // case binary_op
  if(strcmp(node->type, "binary_op") == 0){
    int v1;
    if(strcmp(node->scopes->type, "fcall") == 0) {
      v1 = traverse(node->scopes, args);
      EARLY_RETURN = 0;
    } else {
      v1 = find_bin_op(node->scopes, args);    
    }
    int v2;
    if(strcmp(node->scopes->next->type, "fcall") == 0) {
      v2 = traverse(node->scopes->next, args);
      EARLY_RETURN = 0;
    } else {
      v2 = find_bin_op(node->scopes->next, args);
    }

    if(strcmp(node->extra, "+") == 0) {
      result = v1 + v2;
      node->return_value = result;
      return result;
    }
    if(strcmp(node->extra, "-") == 0) {
      result = v1 - v2;
      node->return_value = result;
      return result;
    }
  }
  // case fcall 
  if(strcmp(node->type, "fcall") == 0){
    struct scope * func = find_func(node->extra);
    // syncs the values of fcall with global, takes in to consideration skip_update 
    update_args(node->args, args);
    // if fcall has scope we execute the scope before attributing the value to the argument
    if(node->scopes != NULL) {
      result = traverse(node->scopes, node->args);
      printf("body exec result: %d\n", result);
    }
    // this function syncs the args values on fcall with the args of the calling function
    update_args(func->args, node->args);
    // func->scopes is always the body of the function
    result = traverse(func->scopes, func->args);
    EARLY_RETURN = 0;
    node->return_value = result;
    return result;
  }
  // case if
  if(strcmp(node->type, "if") == 0) {
    struct scope * comp = node->scopes;
    struct scope * body = node->scopes->next;
    int v1;
    int v2;
    if(strcmp(comp->scopes->type, "iden") == 0) {
      v1 = find_iden(comp->scopes->extra,args, 1)->value;
    } else {
      v1 = comp->scopes->value;
    }
    if(strcmp(comp->scopes->next->type, "iden") == 0) {
      v2 = find_iden(comp->scopes->next->extra,args, 1)->value;
    } else {
      v2 = comp->scopes->next->value;
    }

    if(strcmp(comp->extra, "<") == 0) {
      if(v1 < v2) {
        // executes the body
        result = traverse(body, args);
      }
    }

    if(strcmp(comp->extra, ">") == 0) {
      if(v1 > v2) {
        // executes the body
        result = traverse(body, args);
      }
    }

    if(strcmp(comp->extra, "==") == 0) {
      if(v1 == v2) {
        // executes the body
        result = traverse(body, args);
      }
    }

    return result;
  }
  // case assignment
  if(strcmp(node->type, "assignment") == 0) {
    if(strcmp(node->scopes->type, "iden") == 0) {
      struct arg * iden = find_iden(node->scopes->extra, args, 1); 

      if(strcmp(node->scopes->next->type, "number") == 0) {
        iden->value =  node->scopes->next->value;
      }

      if(strcmp(node->scopes->next->type, "fcall") == 0) {
        result = traverse(node->scopes->next, args);
        EARLY_RETURN = 0;
        iden->value = result;
      }

      if(strcmp(node->scopes->next->type, "binary_op") == 0) {
        result = traverse(node->scopes->next, args);
        iden->value = result;
      }
      return result;
    } else {
      printf("ERROR: assigning to a non identifier!\n");
      exit(1);
    }
  }
  if(strcmp(node->type, "iden") == 0) {
    return find_iden(node->extra, args, 1)->value;
  }
  if(strcmp(node->type, "number") == 0) {
    return node->value;
  }
  struct scope * inode = node->scopes;
  while(inode != NULL) {
    // we do not execute functions definition
    if(strcmp(inode->type, "function") != 0) {
      result = traverse(inode, args);  
    }
    if(strcmp(inode->type, "return") == 0 || 
       EARLY_RETURN == 1) {
      EARLY_RETURN = 1;
      break;
    }
    inode = inode->next;
  }
  node->return_value = result;
  return node->return_value;
}

void exec(struct scope * global) {
  GLOBAL_SCOPE = global->scopes;
  traverse(global, global->args);
}
