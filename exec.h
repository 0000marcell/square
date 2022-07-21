#ifndef PARSER_H
#define PARSER_H

typedef struct {
  char *key;
  int  value;
} arg;

struct scope {
  char * type;
  arg args[100];
  int value;
  int scopescount;
  struct scope *scopes[100];
  int return_value;
};

void exec(struct scope * global);

#endif
