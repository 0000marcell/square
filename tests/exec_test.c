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

void third_case() {
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
            .value = 0,
            .scopescount = 1,
            .scopes = {
              &(struct scope) {
                .type = "number",
                .value = 1
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

int main() {
  // function with one if statement returning 99
  //first_case();
  // function with two if statements second one returning 99 first returning 0
  //second_case();

  third_case();
  return 0;
}
