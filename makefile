default:
	clear
	flex  -l square.l
	bison -dv -Wcounterexamples square.y 
	gcc -g -Wall -Wextra -c exec.c -o ./lib/exec.o
	gcc -g ./lib/exec.o -o square square.tab.c lex.yy.c -lfl
