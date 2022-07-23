#/usr/bin/bash

rm -rf ./a.out
gcc -g -Wall -Wextra -c exec.c -o ./lib/exec.o
gcc -g -Wall -Wextra -c ./tests/exec_test.c -o ./lib/exec_test.o
gcc -g -Wall -Wextra ./lib/exec.o ./lib/exec_test.o
./a.out
