default:
	clear
	flex -l square.l
	bison -dv square.y 
	gcc -o square square.tab.c lex.yy.c -lfl
