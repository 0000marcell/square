#ifndef PARSER_H
#define PARSER_H

typedef struct {
  char *key;
  int  value;
} arg;

typedef struct {
  char * cur;
  char * cal;
} vmap;

struct scope {
  char * type;
  char * extra;
  int argscount;
  arg args[100];
  vmap vmap;
  int value;
  int scopescount;
  struct scope *scopes[100];
  int return_value;
};

void exec(struct scope * global);

#endif
