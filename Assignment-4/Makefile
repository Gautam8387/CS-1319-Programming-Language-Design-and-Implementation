.SUFFIXES: 

translator: 3_A4.y 3_A4_translator.c 3_A4.l
	bison -d 3_A4.y
	flex -o lex.yy.c 3_A4.l
	gcc 3_A4_translator.c 3_A4.tab.c lex.yy.c -lfl -Werror -o translator

build: translator

test: translator
	./translator < 3_A4.nc > test.out

clean:
	rm -f translator lex.yy.c 3_A4.tab.c 3_A4_translator.tab.h test.out 3_A4.tab.o 3_A4.tab.h