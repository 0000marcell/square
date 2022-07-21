#/usr/bin/bash

gcc -Wall -Wextra -c exec.c -o ./lib/exec.o
gcc -Wall -Wextra -c ./tests/exec_test.c -o ./lib/exec_test.o
gcc -Wall -Wextra ./lib/exec.o ./lib/exec_test.o
./a.out
