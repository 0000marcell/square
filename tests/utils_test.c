#include "../exec.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

struct scope global = {
  .type = "function",
  .extra = "global",
  .return_value = 0,
  .args = &(struct arg) {
    .key = "n",
    .value = 1,
    .next = &(struct arg) {
      .key = "k",
      .value = 99,
      .next = &(struct arg) {
        .key = "j",
        .value = 88
      }
    }
  },
  .scopes = &(struct scope) {
    .type = "body",
    .scopes = &(struct scope) {
      .type = "if",
      .scopes = &(struct scope) {
        .type = "comp",
        .extra = "<",
        .scopes = &(struct scope) {
          .type = "iden",
          .extra = "n",
          .next = &(struct scope) {
            .type = "number",
            .value = 2
          },
        },
        .next = &(struct scope) {
          .type = "body",
          .scopes = &(struct scope) {
            .type = "print",
            .scopes = &(struct scope) {
              .type = "number",
              .value = 887
            },
            .next = &(struct scope) {
              .type = "print",
              .scopes = &(struct scope) {
                .type = "iden",
                .extra = "n"
              }
            }
          },
        }
      }
    }
  }
};

int main() {
  printf(">>>>> running utils tests\n");
  struct scope * result = dupscope(&global);
  assert(result->scopes->scopes->scopes->next->scopes->scopes->value == 887);
}
