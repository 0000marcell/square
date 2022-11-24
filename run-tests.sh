#/usr/bin/bash

rm -rf ./a.out
gcc -g -Wall -Wextra -c exec.c -o ./lib/exec.o
gcc -g -Wall -Wextra -c ./tests/exec_test.c -o ./lib/exec_test.o
gcc -g -Wall -Wextra ./lib/exec.o ./lib/exec_test.o
./a.out

rm -rf ./a.out
gcc -g -Wall -Wextra -c exec.c -o ./lib/exec.o
gcc -g -Wall -Wextra -c ./tests/utils_test.c -o ./lib/utils_test.o
gcc -g -Wall -Wextra ./lib/exec.o ./lib/utils_test.o
./a.out
