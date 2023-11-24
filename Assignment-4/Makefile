.SUFFIXES: 

parser: 3_A4.y 3_parser.c 3_A4.l
	bison -d 3_A4.y
	flex -o lex.yy.c 3_A4.l
	gcc 3_parser.c 3_parser.tab.c lex.yy.c -lfl -Werror -o parser

build: parser

test: parser
	./parser < Test.calc