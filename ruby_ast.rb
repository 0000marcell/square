require 'ripper'
require 'pp'
code = <<STR
n = 1
if n < 2
  puts n
end
STR
puts code
pp Ripper.sexp(code)
