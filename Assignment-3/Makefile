build:
	bison -d 3_A3.y 
	flex -o lex.yy.c 3_A3.l
	gcc -o parser lex.yy.c 3_A3.tab.c 3_A3.c -lfl -Werror

clean-head:
	rm -f lex.yy.c 3_A3.tab.c 3_A3.tab.h

clean-all: clean-head
	rm -f parser output.txt

test: build
	./parser < 3_A3.nc

test-out: build
	./parser < 3_A3.nc > output.txt

conflict:
	bison -d 3_A3.y -t -Wcounterexamples
	flex -o lex.yy.c 3_A3.l
	gcc -o parser lex.yy.c 3_A3.tab.c 3_A3.c -lfl -Werror
	./parser < 3_A3.nc