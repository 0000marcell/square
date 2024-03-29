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
    .args = &(struct arg){
      .key = "n",
      .value = 1
    },
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "fib",
        .args = &(struct arg){
          .key = "n",
          .value = 999 
        },
        .scopes = &(struct scope) {
          .type = "body",
          .scopes = &(struct scope) {
            .type = "if",
            .scopes = &(struct scope) {
              .type = "comp",
              .extra = "==",
              .scopes = &(struct scope) {
                .type = "iden",
                .extra = "n",
                .next = &(struct scope) {
                  .type = "number",
                  .value = 2,
                },
              },
              .next = &(struct scope) {
                .type = "body",
                .scopes = &(struct scope) {
                  .type = "return",
                  .scopes = &(struct scope) {
                    .type = "number",
                    .value = 1
                  }
                }
              }
            },
            .next = &(struct scope) {
              .type = "number",
              .value = 888
            },
          },
        },
        .next = &(struct scope) {
          .type = "fcall",
          .extra = "fib",
          .args = &(struct arg) {
            .key = "n",
            .skip_update = 1,
            .value = 2
          }
        },
      },
    }
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.return_value);
  assert(global.return_value == 1);
}

void return_with_binary_op() {
  printf("running tests...\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .return_value = 0,
    .args = &(struct arg){
      .key = "n",
      .value = 1
    },
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "fib",
        .args = &(struct arg){
          .key = "n",
          .value = 999 
        },
        .scopes = &(struct scope) {
          .type = "body",
          .scopes = &(struct scope) {
            .type = "if",
            .scopes = &(struct scope) {
              .type = "comp",
              .extra = "==",
              .scopes = &(struct scope) {
                .type = "iden",
                .extra = "n",
                .next = &(struct scope) {
                  .type = "number",
                  .value = 2,
                },
              },
              .next = &(struct scope) {
                .type = "body",
                .scopes = &(struct scope) {
                  .type = "return",
                  .scopes = &(struct scope) {
                    .type = "body",
                    .scopes = &(struct scope) {
                      .type = "binary_op",
                      .extra = "-",
                      .scopes = &(struct scope) {
                        .type = "iden",
                        .extra = "n",
                        .next = &(struct scope) {
                          .type = "number",
                          .value = 1
                        },
                      },
                    },
                  },
                }
              }
            },
            .next = &(struct scope) {
              .type = "number",
              .value = 888
            },
          },
        },
        .next = &(struct scope) {
          .type = "fcall",
          .extra = "fib",
          .args = &(struct arg) {
            .key = "n",
            .skip_update = 1,
            .value = 2
          },
        },
      },
    }
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.return_value);
  assert(global.return_value == 1);
}

void return_with_fcall_and_bin_op() {
  printf("running tests...\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .return_value = 0,
    .args = &(struct arg){
      .key = "n",
      .value = 1
    },
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "add",
        .args = &(struct arg){
          .key = "n",
          .value = 999 
        },
        .scopes = &(struct scope) {
          .type = "body",
          .scopes = &(struct scope) {
            .type = "return",
            .scopes = &(struct scope) {
              .type = "body",
              .scopes = &(struct scope) {
                .type = "assignment",
                .scopes = &(struct scope) {
                  .type = "iden",
                  .extra = "n",
                  .next = &(struct scope) {
                    .type = "binary_op",
                    .extra = "+",
                    .scopes = &(struct scope) {
                      .type = "iden",
                      .extra = "n",
                      .next = &(struct scope) {
                        .type = "number",
                        .value = 1
                      }
                    }
                  }
                }
              },
            },
          },
        },
        .next = &(struct scope) {
          .type = "function",
          .extra = "main",
          .args = &(struct arg) {
            .key = "n",
            .value = 999
          },
          .scopes = &(struct scope) {
            .type = "body",
            .scopes = &(struct scope) {
              .type = "return",
              .scopes = &(struct scope) {
                .type = "body",
                .scopes = &(struct scope) {
                  .type = "binary_op",
                  .extra = "+",
                  .scopes = &(struct scope) {
                    .type = "fcall",
                    .extra = "add",
                    .args = &(struct arg) {
                      .key = "n"
                    },
                    .scopes = &(struct scope) {
                      .type = "assignment",
                      .scopes = &(struct scope) {
                        .type = "iden",
                        .extra = "n",
                        .next = &(struct scope) {
                          .type = "binary_op",
                          .extra = "+",
                          .scopes = &(struct scope) {
                            .type = "iden",
                            .extra = "n",
                            .next = &(struct scope) {
                              .type = "number",
                              .value = 1
                            }
                          }
                        }
                      }
                    },
                    .next = &(struct scope) {
                      .type = "fcall",
                      .extra = "add",
                      .args = &(struct arg) {
                        .key = "n"
                      },
                      .scopes = &(struct scope) {
                        .type = "assignment",
                        .scopes = &(struct scope) {
                          .type = "iden",
                          .extra = "n",
                          .next = &(struct scope) {
                            .type = "binary_op",
                            .extra = "+",
                            .scopes = &(struct scope) {
                              .type = "iden",
                              .extra = "n",
                              .next = &(struct scope) {
                                .type = "number",
                                .value = 1
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          },
          .next = &(struct scope) {
            .type = "assignment",
            .scopes = &(struct scope) {
              .type = "iden",
              .extra = "n",
              .next = &(struct scope) {
                .type = "fcall",
                .extra = "main",
                .args = &(struct arg) {
                  .key = "n",
                  .skip_update = 1,
                  .value = 1
                }
              }
            },
            .next = &(struct scope) {
              .type = "print",
              .scopes = &(struct scope) {
                .type = "iden",
                .extra = "n"
              },
            }
          }
        },
      },
    }
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.return_value);
  assert(global.return_value == 6);
}

void return_with_fcall() {
  printf("running tests...\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .return_value = 0,
    .args = &(struct arg){
      .key = "n",
      .value = 1
    },
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "fib",
        .args = &(struct arg){
          .key = "n",
          .value = 999 
        },
        .scopes = &(struct scope) {
          .type = "body",
          .scopes = &(struct scope) {
            .type = "if",
            .scopes = &(struct scope) {
              .type = "comp",
              .extra = "==",
              .scopes = &(struct scope) {
                .type = "iden",
                .extra = "n",
                .next = &(struct scope) {
                  .type = "number",
                  .value = 97,
                },
              },
              .next = &(struct scope) {
                .type = "body",
                .scopes = &(struct scope) {
                  .type = "return",
                  .scopes = &(struct scope) {
                    .type = "body",
                    .scopes = &(struct scope) {
                      .type = "fcall",
                      .extra = "fib",
                      .args = &(struct arg) {
                        .key = "n"
                      },
                      .scopes = &(struct scope) {
                        .type = "body",
                        .scopes = &(struct scope) {
                          .type = "assignment",
                          .scopes = &(struct scope) {
                            .type = "iden",
                            .extra = "n",
                            .next = &(struct scope) {
                              .type = "binary_op",
                              .extra = "-",
                              .scopes = &(struct scope) {
                                .type = "iden",
                                .extra = "n",
                                .next = &(struct scope) {
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
                }
              }
            },
            .next = &(struct scope) {
              .type = "iden",
              .extra = "n"
            },
          },
        },
        .next = &(struct scope) {
          .type = "assignment",
          .scopes = &(struct scope) {
            .type = "iden",
            .extra = "n",
            .next = &(struct scope) {
              .type = "fcall",
              .extra = "fib",
              .args = &(struct arg) {
                .key = "n",
                .skip_update = 1,
                .value = 97
              }
            }
          },
          .next = &(struct scope) {
            .type = "print",
            .scopes = &(struct scope) {
              .type = "iden",
              .extra = "n"
            }
          }
        },
      },
    }
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.args->value);
  assert(global.args->value == 96);
}

void if_case() {
  printf("running tests >>>>>>>>>>>\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .return_value = 0,
    .args = &(struct arg) {
      .key = "n",
      .value = 1 
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
              .type = "number",
              .value = 999
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

void print_case() {
  printf("running tests >>>>>>>>>>>\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .return_value = 0,
    .args = &(struct arg) {
      .key = "n",
      .value = 1 
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
                .value = 999
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
  exec(&global);
  printf(">>>>> return_value %d\n", global.return_value);
  assert(global.return_value == 1);
}

void assignment_case() {
  printf("running tests >>>>>>>>>>>\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .return_value = 0,
    .args = &(struct arg) {
      .key = "n",
      .value = 1 
    },
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "assignment",
        .scopes = &(struct scope) {
          .type = "iden",
          .extra = "n",
          .next = &(struct scope) {
            .type = "number",
            .value = 997
          },
        },
      }
    }
  };
  exec(&global);
  printf(">>>>> return_value %d\n", global.args[0].value);
  assert(global.args[0].value == 997);
}



void fcall_case() {
  printf("running tests >>>>>>>>>>>\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .return_value = 0,
    .args = &(struct arg){
      .key = "x",
      .value = 999
    },
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "fib",
        .args = &(struct arg) {
          .key = "n",
          .value = 888 
        },
        .scopes = &(struct scope) {
          .type = "body",
          .scopes = &(struct scope) {
            .type = "iden",
            .extra = "n",
          }
        },
        .next = &(struct scope) {
          .type = "assignment",
          .scopes = &(struct scope) {
            .type = "iden",
            .extra = "x",
            .next = &(struct scope) {
              .type = "fcall",
              .extra = "fib",
              .args = &(struct arg) {
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
    .return_value = 0,
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "fib",
        .args = &(struct arg) {
          .key = "n",
          .value = 888 
        },
        .scopes = &(struct scope) {
          .type = "body",
          .scopes = &(struct scope) {
            .type = "assignment",
            .scopes = &(struct scope) {
              .type = "iden",
              .extra = "n",
              .next = &(struct scope) {
                .type = "binary_op",
                .extra = "+",
                .scopes = &(struct scope) {
                  .type = "iden",
                  .extra = "n",
                  .next = &(struct scope) {
                    .type = "number",
                    .value = 1
                  }
                },
              },
            },
            .next = &(struct scope) {
              .type = "iden",
              .extra = "n"
            }
          },
        },
        .next = &(struct scope) {
          .type = "fcall",
          .extra = "fib",
          .args = &(struct arg) {
            .key = "n",
            .skip_update = 1,
            .value = 1
          },
          .return_value = 777
        }
      }
    }
  };
  exec(&global);
  printf(">>>>> return value %d\n", global.return_value);
  assert(global.return_value == 2);
}

void binary_op_with_fcalls() {
  printf("running tests >>>>>>>>>>>\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .args = &(struct arg) {
      .key = "n",
      .value = 999
    },
    .return_value = 0,
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "add",
        .args = &(struct arg) {
          .key = "n",
          .value = 888 
        },
        .scopes = &(struct scope) {
          .type = "body",
          .scopes = &(struct scope) {
            .type = "assignment",
            .scopes = &(struct scope) {
              .type = "iden",
              .extra = "n",
              .next = &(struct scope) {
                .type = "binary_op",
                .extra = "+",
                .scopes = &(struct scope) {
                  .type = "iden",
                  .extra = "n",
                  .next = &(struct scope) {
                    .type = "number",
                    .value = 1
                  }
                },
              },
            },
            .next = &(struct scope) {
              .type = "iden",
              .extra = "n"
            }
          },
        },
        .next = &(struct scope) {
          .type = "function",
          .extra = "main",
          .args = &(struct arg) {
            .key = "n",
            .value = 999
          },
          .scopes = &(struct scope) {
            .type = "body",
            .scopes = &(struct scope) {
              .type = "assignment",
              .scopes = &(struct scope) {
                .type = "iden",
                .extra = "n",
                .next = &(struct scope) {
                  .type = "binary_op",
                  .extra = "+",
                  .scopes = &(struct scope) {
                    .type = "fcall",
                    .extra = "add",
                    .args = &(struct arg) {
                      .key = "n"
                    },
                    .next = &(struct scope) {
                      .type = "fcall",
                      .extra = "add",
                      .args = &(struct arg) {
                        .key = "n"
                      },
                    }
                  }
                }
              },
              .next = &(struct scope) {
                .type = "iden",
                .extra = "n"
              }
            }
          },
          // after the main function
          .next = &(struct scope) {
            .type = "assignment",
            .scopes = &(struct scope) {
              .type = "iden",
              .extra = "n",
              .next = &(struct scope) {
                .type = "fcall",
                .extra = "main",
                .args = &(struct arg) {
                  .key = "n",
                  .skip_update = 1,
                  .value = 1
                }
              }
            }
          }
        }
      }
    }
  };
  exec(&global);
  printf(">>>>> return value %d\n", global.args->value);
  assert(global.args->value == 4);
}

void fib_simplified_version() {
  // fibonacci 
  printf("running tests...\n");
  struct scope global = {
    .type = "function",
    .extra = "global",
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "fib",
        .args = &(struct arg) {
          .key = "n",
          .value = 99
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
                  .value = 3,
                },
              },
              .next = &(struct scope) {
                .type = "body",
                .scopes = &(struct scope) {
                  .type = "return",
                  .scopes = &(struct scope) {
                    .type = "binary_op",
                    .extra = "-",
                    .scopes = &(struct scope) {
                      .type = "iden",
                      .extra = "n",
                      .next = &(struct scope) {
                        .type = "number",
                        .value = 1
                      },
                    },
                  },
                },
              },
            },
            .next = &(struct scope) {
              .type = "binary_op",
              .extra = "+",
              .scopes = &(struct scope) {
                .type = "fcall",
                .extra = "fib",
                .args = &(struct arg) {
                  .key = "n"
                },
                .scopes = &(struct scope) {
                  .type = "assignment",
                  .scopes = &(struct scope) {
                    .type = "iden",
                    .extra = "n",
                    .next = &(struct scope) {
                      .type = "binary_op",
                      .extra = "-",
                      .scopes = &(struct scope) {
                        .type = "iden",
                        .extra = "n",
                        .next = &(struct scope) {
                          .type = "number",
                          .value = 1
                        }
                      },
                    },
                  },
                },
                .next = &(struct scope) {
                  .type = "fcall",
                  .extra = "fib",
                  .args = &(struct arg) {
                    .key = "n"
                  },
                  .scopes = &(struct scope) {
                    .type = "assignment",
                    .scopes = &(struct scope) {
                      .type = "iden",
                      .extra = "n",
                      .next = &(struct scope) {
                        .type = "binary_op",
                        .extra = "-",
                        .scopes = &(struct scope) {
                          .type = "iden",
                          .extra = "n",
                          .next = &(struct scope) {
                            .type = "number",
                            .value = 2
                          },
                        },
                      },
                    },
                  },
                }
              }
            }
          },
        },
        .next = &(struct scope) {
          .type = "fcall",
          .extra = "fib",
          .args = &(struct arg) {
            .key = "n",
            .skip_update = 1,
            .value = 2
          },
        },
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
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "fib",
        .args = &(struct arg) {
          .key = "n",
          .value = 99
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
                  .type = "assignment",
                  .scopes = &(struct scope) {
                    .type = "iden",
                    .extra = "n",
                    .next = &(struct scope) {
                      .type = "binary_op",
                      .extra = "+",
                      .scopes = &(struct scope) {
                        .type = "iden",
                        .extra = "n",
                        .next = &(struct scope) {
                          .type = "number",
                          .value = 1
                        }
                      }
                    }
                  },
                  .next = &(struct scope) {
                    .type = "fcall",
                    .extra = "fib",
                    .args = &(struct arg){
                      .key = "n",
                    }
                  },
                },
              },
            },
            .next = &(struct scope) {
              .type = "iden",
              .extra = "n"
            }
          },
        },
        .next = &(struct scope) {
          .type = "fcall",
          .extra = "fib",
          .args = &(struct arg) {
            .key = "n",
            .skip_update = 1,
            .value = 1
          },
        }
      }
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
    .scopes = &(struct scope) {
      .type = "body",
      .scopes = &(struct scope) {
        .type = "function",
        .extra = "fib",
        .args = &(struct arg) {
          .key = "n",
        },
        .scopes = &(struct scope) {
          .type = "body",
          .scopes = &(struct scope) {
            .type = "if",
            .scopes = &(struct scope) {
              .type = "comp",
              .extra = ">",
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
                  .type = "assignment",
                  .scopes = &(struct scope) {
                    .type = "iden",
                    .extra = "n",
                    .next = &(struct scope) {
                      .type = "fcall",
                      .extra = "fib",
                      .args = &(struct arg) {
                        .key = "n"
                      },
                      .scopes = &(struct scope) {
                        .type = "body",
                        .scopes = &(struct scope) {
                          .type = "assignment",
                          .scopes = &(struct scope) {
                            .type = "iden",
                            .extra = "n",
                            .next = &(struct scope) {
                              .type = "binary_op",
                              .extra = "-",
                              .scopes = &(struct scope) {
                                .type = "iden",
                                .extra = "n",
                                .next = &(struct scope) {
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
                  .next = &(struct scope) {
                    .type = "fcall",
                    .extra = "fib",
                    .args = &(struct arg) {
                      .key = "n",
                    }
                  },
                },
              },
            },
            .next = &(struct scope) {
              .type = "iden",
              .extra = "n"
            }
          },
        },
        .next = &(struct scope) {
          .type = "fcall",
          .extra = "fib",
          .args = &(struct arg) {
            .key = "n",
            .skip_update = 1,
            .value = 4
          }
        }
      }
    },
    .return_value = 99
  };
  exec(&global);
  printf(">>>>> args value %d\n", global.return_value);
  assert(global.return_value == 2);
}

int main() {
  //if_case();
  
  //assignment_case();

  //fcall_case();

  //binary_op_case();

  //binary_op_with_fcalls();
  
  //recursive_case();

  // doing operation inside the arguments 
  //fcall_with_scopes();

  //early_return();

  /* return_with_binary_op(); */

  /* return_with_fcall(); */

  return_with_fcall_and_bin_op();

  //fib_simplified_version();

  // print case
  //print_case();

  return 0;
}
