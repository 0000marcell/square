# Square Language 

This is toy language built for learning purposes, the plan is to use flex and bison
to create an AST then transform the AST to x86 instructions  
the language will have the following syntax.

```
[>:fib n:
  [:if n < 3:
    return n - 1
  ]
  return [:fib n - 1] + [:fib n - 2]
]
[:fib 10]
```

# No need for return statements if it's the last line

```
[>:fib n:
  [:if n == 999:
    return [:fib n - 10]  
  ]
  n
]

n = [:fib 999]
```
