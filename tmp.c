#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  int return_value;
};

struct scope global = {
  .type = "function",
  .extra = "global",
  .return_value = 0,
  .scopes = &(struct scope) {
    .type = "body",
    .scopes = &(struct scope) {
      .type = "if",
      .next = &(struct scope) {
        .type = "id",
        .scopes = &(struct scope) {
          .type = "fcall"
        },
        .next = &(struct scope) {
          .type = "number",
          .next = &(struct scope) {
            .type = "assignment",
          }
        }
      }
    }
  }
};

struct scope * find_body(struct scope * sc) {
  int didfind = 0;
  struct scope * tmp = sc;
  while(tmp != NULL) {
    if(strcmp(tmp->type, "body") == 0) {
      didfind = 1;
      break;
    }
    tmp = tmp->next;
  }
  if(didfind == 0) {
    printf("ERROR: could not find body on scope %s\n", sc->type);
    exit(1);
  }
  return tmp;
}

struct scope * find_body_next_address(struct scope * sc) {
  struct scope * body = find_body(sc->scopes);
  struct scope * tmp = body->scopes;
  while(tmp != NULL) {
    if(tmp->next == NULL) {
      break;
    }
    tmp = tmp->next;
  };
  return tmp;
}


int main(int argc, char *argv[]) {
  printf("value: %s\n", argv[1]); 
  return 0;  
}
