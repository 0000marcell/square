# Square language 

This is toy language built when I was learning about programming languages 
and assembly x86, the language has a VM that transform the AST in to x86 instructions
please don't use this for anything

```
def fib(n)

    if n == 0
        return 0
    end
    if n == 1
        return 1
    end

    if n >= 2
        return fib(n-1) + (fib(n-2))
    end

end
```

```
[:program
  [:add a b 
    a+b 
  ]

  [:print [:add 1 1]]

  [:if a > b; 
    
  ] 
]
```
# square
