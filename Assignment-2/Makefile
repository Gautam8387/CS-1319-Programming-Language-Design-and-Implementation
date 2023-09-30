all:
	flex -o 3_A2.yy.c 3_A2.l
	gcc 3_A2.yy.c 3_A2.c -ll -o lexer.out
	./lexer.out < 3_A2.nc

clean:
	rm lexer.out 3_A2.yy.c

build: clean
	flex -o 3_A2.yy.c 3_A2.l
	gcc 3_A2.yy.c 3_A2.c -ll -o lexer.out

test: build
	./lexer.out < 3_A2.nc