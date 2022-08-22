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
  printf(">>>>> return_value %d\n", global.return_value);
  assert(global.return_value == 999);
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



void fcall_case() {
  printf("running tests >>>>>>>>>>>\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .scopescount = 2,
    .return_value = 0,
    .argscount = 1,
    .args = {
      {
        .key = "x",
        .value = 999
      }
    },
    .scopes = {
      &(struct scope) {
        .type = "function",
        .extra = "fib",
        .scopescount = 1,
        .argscount = 1,
        .args = {
          {
            .key = "n",
            .value = 888 
          }
        },
        .scopes = {
          &(struct scope) {
            .type = "body",
            .scopescount = 1,
            .scopes = {
              &(struct scope) {
                .type = "iden",
                .extra = "n",
              }
            }
          }
        }
      },
      &(struct scope) {
        .type = "assignment",
        .scopescount = 2,
        .scopes = {
          &(struct scope) {
            .type = "iden",
            .extra = "x",
          },
          &(struct scope) {
            .type = "fcall",
            .extra = "fib",
            .argscount = 1,
            .args = {
              {
                .key = "n",
                .value = 777
              }
            }
          }
        }
      }
    }
  };
  exec(&global);
  printf(">>>>> args value %d\n", global.args[0].value);
  assert(global.args[0].value == 777);
}

void binary_op_case() {
  printf("running tests >>>>>>>>>>>\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .scopescount = 2,
    .return_value = 0,
    .scopes = {
      &(struct scope) {
        .type = "function",
        .extra = "fib",
        .argscount = 1,
        .args = {
          {
            .key = "n",
            .value = 888 
          }
        },
        .scopescount = 1,
        .scopes = {
          &(struct scope) {
            .type = "body",
            .scopescount = 2,
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
                    .type = "binary_op",
                    .extra = "+",
                    .scopescount = 2,
                    .scopes = {
                      &(struct scope) {
                        .type = "iden",
                        .extra = "n"
                      },
                      &(struct scope) {
                        .type = "number",
                        .value = 1
                      }
                    }
                  }
                }
              },
              &(struct scope) {
                .type = "iden",
                .extra = "n"
              }
            }
          }
        }
      },
      &(struct scope) {
        .type = "fcall",
        .extra = "fib",
        .argscount = 1,
        .args = {
          {
            .key = "n",
            .value = 1
          }
        },
        .return_value = 777
      }
    }
  };
  exec(&global);
  printf(">>>>> return value %d\n", global.return_value);
  assert(global.return_value == 2);
}

void recursive_case() {
  // function with recursive calls, fib > 2
  printf("running tests...\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .scopescount = 2,
    .scopes = {
      &(struct scope) {
        .type = "function",
        .extra = "fib",
        .argscount = 1,
        .args = {
          {
            .key = "n",
            .value = 99
          }
        },
        .scopescount = 1,
        .scopes = {
          &(struct scope) {
            .type = "body",
            .scopescount = 2,
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
                    },
                  },
                  &(struct scope) {
                    .type = "body",
                    .scopescount = 2,
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
                            .type = "binary_op",
                            .extra = "+",
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
                        .extra = "fib",
                        .argscount = -1, // that's the way we identify to use the variable
                        .args = {
                          {
                            .key = "n", // this is a mapping, we want to grab the value of the variable n in the current scope and change the value of the variable n in the function scope
                          }
                        }
                      },   
                    },
                  },
                },
              },
              &(struct scope) {
                .type = "iden",
                .extra = "n"
              }
            }
          }
        }
      },
      &(struct scope) {
        .type = "fcall",
        .extra = "fib",
        .argscount = 1,
        .args = {
          {
            .key = "n",
            .value = 1
          }
        }
      },
    },
    .return_value = 99
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.return_value);
  assert(global.return_value == 2);
}

int main() {
  // function with one if statement returning 99
  //first_case();
  // function with two if statements second one returning 99 first returning 0
  //second_case();
  
  // if statement executing the if statement
  //if_case();
  // assignment case
  //assignment_case();

  // function call case
  //fcall_case();

  // binary_op case 
  //binary_op_case();

  // recursive_case
  recursive_case();

  return 0;
}
