#ifndef PARSER_H
#define PARSER_H

struct arg {
  char *key;
  int  value;
  int  skip_update;
  struct arg * next; 
};

struct scope {
  char * type;
  char * extra;
  struct arg * args;
  int value;
  struct scope * scopes;
  struct scope * next; 
  struct scope * prev; 
  int return_value;
};

struct arg * find_iden(char * str, struct arg * args, int abort);

void update_args(struct arg * fargs, struct arg * nargs);

struct arg * dupargs(struct arg * cargs);

struct scope * dupscope(struct scope * cscope);

void exec(struct scope * global);

#endif
