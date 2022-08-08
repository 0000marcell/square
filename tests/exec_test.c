#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../exec.h"

void first_case() {
  // function with one if statement returning 99
  printf("running tests...\n");
  struct scope global = {
    .type = "global",
    .scopescount = 1,
    .scopes = {
      &(struct scope) {
        .type = "fib",
        .args = {
          {
            .key = "n",
            .value = 1 
          }
        },
        .scopescount = 1,
        .scopes = {
          &(struct scope) {
            .type = "if",
            .value = 1,
            .scopescount = 1,
            .scopes = {
              &(struct scope) {
                .type = "number",
                .value = 0
              }
            },
            .return_value = 99
          },
        },
        .return_value = 99
      }
    },
    .return_value = 99
  }; 
  exec(&global);
  printf(">>>>> return_value %d\n", global.scopes[0]->return_value);
  assert(global.scopes[0]->return_value == 0);
}

void second_case() {
  // function with two if statement returning 99
  printf("running tests...\n");
  struct scope global = {
    .type = "global",
    .scopescount = 1,
    .scopes = {
      &(struct scope) {
        .type = "fib",
        .args = {
          {
            .key = "n",
            .value = 1 
          }
        },
        .scopescount = 2,
        .scopes = {
          &(struct scope) {
            .type = "if",
            .value = 0,
            .scopescount = 1,
            .scopes = {
              &(struct scope) {
                .type = "number",
                .value = 0
              }
            },
            .return_value = 99
          },
          &(struct scope) {
            .type = "if",
            .value = 1,
            .scopescount = 1,
            .scopes = {
              &(struct scope) {
                .type = "number",
                .value = 1
              }
            },
            .return_value = 99
          },
        },
        .return_value = 99
      }
    },
    .return_value = 99
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.scopes[0]->return_value);
  assert(global.scopes[0]->return_value == 1);
}

void if_case() {
  printf("running tests >>>>>>>>>>>\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .scopescount = 1,
    .return_value = 0,
    .argscount = 1,
    .args = {
      {
        .key = "n",
        .value = 1 
      }
    },
    .scopes = {
      &(struct scope) {
        .type = "if",
        .scopescount = 2,
        .scopes = {
          &(struct scope) {
            .type = "comp",
            .extra = "<",
            .scopescount = 2,
            .scopes = {
              &(struct scope) {
                .type = "iden",
                .extra = "n"
              },
              &(struct scope) {
                .type = "number",
                .value = 2
              },
            }
          },
          &(struct scope) {
            .type = "body",
            .scopescount = 1,
            .scopes = {
              &(struct scope) {
                .type = "number",
                .value = 999
              }
            }
          }
        }
      }
    }
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.scopes[0]->return_value);
  assert(global.scopes[0]->return_value == 999);
}

void assignment_case() {
  printf("running tests >>>>>>>>>>>\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .scopescount = 1,
    .return_value = 0,
    .argscount = 1,
    .args = {
      {
        .key = "n",
        .value = 1 
      }
    },
    .scopes = {
      &(struct scope) {
        .type = "assignment",
        .scopescount = 2,
        .scopes = {
          &(struct scope) {
            .type = "iden",
            .extra = "n"
          },
          &(struct scope) {
            .type = "number",
            .value = 997
          },
        }
      }
    }
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.scopes[0]->return_value);
  assert(global.args[0].value == 997);
}

void recursive_case() {
  // function with recursive calls, fib > 2
  printf("running tests...\n");
  struct scope global = {
    .type = "global",
    .scopescount = 1,
    .scopes = {
      &(struct scope) {
        .type = "fib",
        .args = {
          {
            .key = "n",
            .value = 1 
          }
        },
        .scopescount = 1,
        .scopes = {
          &(struct scope) {
            .type = "if",
            .scopescount = 4,
            .scopes = {
              &(struct scope) {
                .type = "comp",
                .extra = "<",
                .scopescount = 2,
                .scopes = {
                  &(struct scope) {
                    .type = "iden",
                    .extra = "n"
                  },
                  &(struct scope) {
                    .type = "number",
                    .value = 2
                  },
                },
              },
              &(struct scope) {
                .type = "print",
                .scopescount = 1,
                .scopes = {
                  &(struct scope) {
                    .type = "iden",
                    .extra = "n"
                  },
                },
              },
              &(struct scope) {
                .type = "assignment",
                .scopescount = 2,
                .scopes = {
                  &(struct scope) {
                    .type = "iden",
                    .extra = "n"
                  },
                  &(struct scope) {
                    .type = "add",
                    .scopescount = 2,
                    .scopes = {
                      &(struct scope) {
                        .type = "iden",
                        .extra = "n"
                      },
                      &(struct scope) {
                        .type = "number",
                        .value = 1
                      },
                    },
                  },
                },
              },
              &(struct scope) {
                .type = "fcall",
                .extra = "fib"
              },
            },
            .return_value = 99
          },
        },
        .return_value = 99
      }
    },
    .return_value = 99
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.scopes[0]->return_value);
  assert(global.scopes[0]->return_value == 1);
}

int main() {
  // function with one if statement returning 99
  //first_case();
  // function with two if statements second one returning 99 first returning 0
  //second_case();
  
  // function with a if statement executing the if statement
  if_case();
  // function with a assignment case
  assignment_case();
  return 0;
}
