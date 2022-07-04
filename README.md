# Square Language 

This is toy language built for learning purposes, the plan is to use flex and bison
to create an AST then transform the AST to x86 instructions  
the language will have the following syntax.

```
[>:fib n:
  [:if n == 0: 0]
  [:if n == 1: 1]
  [:if n >= 2: 
    [:fib n-1] + [:fib n-2]
  ]
]
[:fib 10]
```
