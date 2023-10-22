all:
	bison -d 3_A3.y
	flex -o lex.yy.c 3_A3.l
	gcc -o parser lex.yy.c 3_A3.tab.c 3_A3.c -lfl -Werror

clean-head:
	rm -f lex.yy.c 3_A3.tab.c 3_A3.tab.h

clean-all: clean-head
	rm -f parser

test:
	./parser < 3_A3.nc