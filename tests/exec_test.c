#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../exec.h"

void early_return() {
  // function that returns ealy 
  printf("running tests...\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .return_value = 0,
    .argscount = 1,
    .args = {
      {
        .key = "n",
        .value = 1 
      }
    },
    .scopescount = 2,
    .scopes = {
      &(struct scope) {
        .type = "function",
        .extra = "fib",
        .argscount = 1,
        .args = {
          {
            .key = "n",
            .value = 999 
          }
        },
        .scopescount = 2,
        .scopes = {
          &(struct scope) {
            .type = "if",
            .scopescount = 2,
            .scopes = {
              &(struct scope) {
                .type = "comp",
                .extra = "==",
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
                    .type = "return",
                    .scopescount = 1,
                    .scopes = {
                      &(struct scope) {
                        .type = "number",
                        .value = 1
                      }
                    }
                  }
                }
              }
            }
          },
          &(struct scope) {
            .type = "number",
            .value = 888
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
            .skip_update = 1,
            .value = 2 
          }
        }
      }
    }
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.scopes[1]->return_value);
  assert(global.scopes[1]->return_value == 1);
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
                .skip_update = 1,
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
            .skip_update = 1,
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

void fib() {
  // fibonacci 
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
                        .value = 3
                      },
                    },
                  },
                  &(struct scope) {
                    .type = "body",
                    .scopescount = 1,
                    .scopes = {
                      &(struct scope) {
                        .type = "return",
                        .scopescount = 1,
                        .scopes = {
                          &(struct scope) {
                            .type = "binary_op",
                            .extra = "-",
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
                    },
                  },
                },
              },
              &(struct scope) {
                .type = "binary_op",
                .extra = "+",
                .scopescount = 2,
                .scopes = {
                  &(struct scope) {
                    .type = "fcall",
                    .extra = "fib",
                    .argscount = 1,
                    .args = {
                      {
                        .key = "n"
                      }
                    },
                    .scopescount = 1,
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
                            .extra = "-",
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
                            },
                          },
                        }
                      },
                    }
                  },
                  &(struct scope) {
                    .type = "fcall",
                    .extra = "fib",
                    .argscount = 1,
                    .args = {
                      {
                        .key = "n"
                      }
                    },
                    .scopescount = 1,
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
                            .extra = "-",
                            .scopescount = 2,
                            .scopes = {
                              &(struct scope) {
                                .type = "iden",
                                .extra = "n"
                              },
                              &(struct scope) {
                                .type = "number",
                                .value = 2
                              }
                            },
                          },
                        },
                      },
                    },
                  },
                }
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
            .skip_update = 1,
            .value = 2
          }
        }
      },
    },
    .return_value = 99
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.return_value);
  assert(global.return_value == 1);
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
                        .argscount = 1,
                        .args = {
                          {
                            .key = "n",
                          }
                        },
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
            .skip_update = 1,
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

void fcall_with_scopes() {
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
                    .extra = ">",
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
                            .type = "fcall",
                            .extra = "fib",
                            .argscount = 1,
                            .args = {
                              {
                                .key = "n"
                              }
                            },
                            .scopescount = 1,
                            .scopes = {
                              &(struct scope) {
                                .type = "body",
                                .scopescount = 1,
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
                                        .extra = "-",
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
                                        },
                                      },
                                    }
                                  },
                                },
                              },
                            },
                          },
                        },
                      },
                      &(struct scope) {
                        .type = "fcall",
                        .extra = "fib",
                        .argscount = 1,
                        .args = {
                          {
                            .key = "n",
                          }
                        },
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
            .skip_update = 1,
            .value = 4
          }
        }
      },
    },
    .return_value = 99
  };
  exec(&global);
  printf(">>>>> args value %d\n", global.return_value);
  assert(global.return_value == 2);
}

int main() {
  // if statement executing the if statement
  //if_case();
  
  //assignment_case();

  //fcall_case();

  // binary_op case 
  //binary_op_case();
  
  //recursive_case();

  // doing operation inside the arguments 
  //fcall_with_scopes();

  //early_return();

  //fibonacci case
  fib();

  return 0;
}
