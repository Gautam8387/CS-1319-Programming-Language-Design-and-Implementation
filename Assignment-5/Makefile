.SUFFIXES: 
GROUP = 3_A5
TEST_DIR = test-cases-assign

compiler: 3_A5.y 3_A5_translator.c 3_A5.l
	bison -d 3_A5.y
	flex -o lex.yy.c 3_A5.l
	gcc -c myl.c
	ar -rcs libmyl.a myl.o
	gcc 3_A5_translator.c 3_A5.tab.c lex.yy.c -lfl -Werror -o compiler

build: compiler

test: compiler
	./compiler 2 3_A5.nc
	gcc -c 3_A5.s
	gcc 3_A5.o -o 3_A5 -L. -lmyl -no-pie

clean:
	rm -f compiler lex.yy.c 3_A5.tab.c 3_A5_translator.tab.h test.tac 3_A5.tab.o 3_A5.tab.h libmyl.a myl.o 3_A5 3_A5.o 3_A5.s 3_A5.tac
	
test-all: compiler
	python3 test-cases.py	

submit: compiler
	mkdir ${TEST_DIR}/x86 && mkdir ${TEST_DIR}/tac && mkdir ${TEST_DIR}/prog
	./compiler 2 ${TEST_DIR}/test1.nc
	./compiler 2 ${TEST_DIR}/test2.nc
	./compiler 2 ${TEST_DIR}/test3.nc
	./compiler 2 ${TEST_DIR}/test4.nc
	./compiler 2 ${TEST_DIR}/test5.nc
	mv ${TEST_DIR}/test1.tac ${TEST_DIR}/tac && mv ${TEST_DIR}/test1.s ${TEST_DIR}/x86
	mv ${TEST_DIR}/test2.tac ${TEST_DIR}/tac && mv ${TEST_DIR}/test2.s ${TEST_DIR}/x86
	mv ${TEST_DIR}/test3.tac ${TEST_DIR}/tac && mv ${TEST_DIR}/test3.s ${TEST_DIR}/x86
	mv ${TEST_DIR}/test4.tac ${TEST_DIR}/tac && mv ${TEST_DIR}/test4.s ${TEST_DIR}/x86
	mv ${TEST_DIR}/test5.tac ${TEST_DIR}/tac && mv ${TEST_DIR}/test5.s ${TEST_DIR}/x86
	gcc -c ${TEST_DIR}/x86/test1.s -o ${TEST_DIR}/x86/test1.o
	gcc -c ${TEST_DIR}/x86/test2.s -o ${TEST_DIR}/x86/test2.o
	gcc -c ${TEST_DIR}/x86/test3.s -o ${TEST_DIR}/x86/test3.o
	gcc -c ${TEST_DIR}/x86/test4.s -o ${TEST_DIR}/x86/test4.o
	gcc -c ${TEST_DIR}/x86/test5.s -o ${TEST_DIR}/x86/test5.o
	gcc ${TEST_DIR}/x86/test2.o -o ${TEST_DIR}/prog/test2 -L. -lmyl -no-pie
	gcc ${TEST_DIR}/x86/test3.o -o ${TEST_DIR}/prog/test3 -L. -lmyl -no-pie
	gcc ${TEST_DIR}/x86/test4.o -o ${TEST_DIR}/prog/test4 -L. -lmyl -no-pie
	gcc ${TEST_DIR}/x86/test5.o -o ${TEST_DIR}/prog/test5 -L. -lmyl -no-pie
	gcc ${TEST_DIR}/x86/test1.o -o ${TEST_DIR}/prog/test1 -L. -lmyl -no-pie