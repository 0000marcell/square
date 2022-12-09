# Square Language 

This is very minimal toy language built for learning purposes, the objective was 
to create a language and write Fibonacci in it, the language uses flex and bison
to parse a simple `AST` that is executed by a C program I have some plans on 
transforming the `AST` into x86 instructions in the future
the language have the following syntax.

## Fibonacci in square 
```
[>:fib n:
  [:if n < 3:
    return n - 1
  ]
  return [:fib n - 1] + [:fib n - 2]
]
[:fib 10]
```

# Function declaration 

```
[>:fib n:
  return n
]
```

# Function calls
```
[:fib 10]
```

# If statements
```
[:if n < 3:
  return n - 1
]
```

# Basic arithmetics
```
1 + 2
x + y
y + 3
```
