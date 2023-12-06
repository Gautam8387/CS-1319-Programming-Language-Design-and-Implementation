.SUFFIXES: 

compiler: 3_A5.y 3_A5_translator.c 3_A5.l
	bison -d 3_A5.y
	flex -o lex.yy.c 3_A5.l
	gcc 3_A5_translator.c 3_A5.tab.c lex.yy.c -lfl -Werror -o compiler

build: compiler

test: compiler
	./compiler < 3_A5.nc > test.out

clean:
	rm -f compiler lex.yy.c 3_A5.tab.c 3_A5_translator.tab.h test.out 3_A5.tab.o 3_A5.tab.h