.SUFFIXES: 
GROUP = 3_A5
TEST_DIR = A5_Tests

compiler: 3_A5.y 3_A5_translator.c 3_A5.l
	bison -d 3_A5.y
	flex -o lex.yy.c 3_A5.l
	gcc -c myl.c
	ar -rcs libmyl.a myl.o
	gcc 3_A5_translator.c 3_A5.tab.c lex.yy.c -lfl -Werror -o compiler

build: compiler

test-nc: compiler
	./compiler 2 3_A5.nc
	mv 3_A5_quads5.out 3_A5_quads_nc.out && mv 3_A5_quads5.asm 3_A5_quads_nc.asm
	as 3_A5_quads_nc.asm -o 3_A5_quads_nc.o
	gcc 3_A5_quads_nc.o -o 3_A5_quads_nc -L. -lmyl -no-pie

clean:
	rm -f compiler lex.yy.c 3_A5.tab.c 3_A5_translator.tab.h test.tac 3_A5.tab.o 3_A5.tab.h libmyl.a myl.o 3_A5 3_A5_quads_nc.o 3_A5_quads_nc.asm 3_A5_quads_nc.out 3_A5_quads_nc
test-all: compiler
	python3 test-cases.py	

test: compiler
	rm -rf ${TEST_DIR}/x86 && rm -rf ${TEST_DIR}/tac && rm -rf ${TEST_DIR}/exe
	mkdir ${TEST_DIR}/x86 && mkdir ${TEST_DIR}/tac && mkdir ${TEST_DIR}/exe
	./compiler 2 ${TEST_DIR}/test1.nc
	./compiler 2 ${TEST_DIR}/test2.nc
	./compiler 2 ${TEST_DIR}/test3.nc
	./compiler 2 ${TEST_DIR}/test4.nc
	./compiler 2 ${TEST_DIR}/test5.nc
	mv 3_A5_quads1.out ${TEST_DIR}/tac && mv 3_A5_quads1.asm ${TEST_DIR}/x86
	mv 3_A5_quads2.out ${TEST_DIR}/tac && mv 3_A5_quads2.asm ${TEST_DIR}/x86
	mv 3_A5_quads3.out ${TEST_DIR}/tac && mv 3_A5_quads3.asm ${TEST_DIR}/x86
	mv 3_A5_quads4.out ${TEST_DIR}/tac && mv 3_A5_quads4.asm ${TEST_DIR}/x86
	mv 3_A5_quads5.out ${TEST_DIR}/tac && mv 3_A5_quads5.asm ${TEST_DIR}/x86
	as ${TEST_DIR}/x86/3_A5_quads1.asm -o ${TEST_DIR}/x86/3_A5_quads1.o
	as ${TEST_DIR}/x86/3_A5_quads2.asm -o ${TEST_DIR}/x86/3_A5_quads2.o
	as ${TEST_DIR}/x86/3_A5_quads3.asm -o ${TEST_DIR}/x86/3_A5_quads3.o
	as ${TEST_DIR}/x86/3_A5_quads4.asm -o ${TEST_DIR}/x86/3_A5_quads4.o
	as ${TEST_DIR}/x86/3_A5_quads5.asm -o ${TEST_DIR}/x86/3_A5_quads5.o
	gcc ${TEST_DIR}/x86/3_A5_quads2.o -o ${TEST_DIR}/exe/3_A5_quads2 -L. -lmyl -no-pie
	gcc ${TEST_DIR}/x86/3_A5_quads3.o -o ${TEST_DIR}/exe/3_A5_quads3 -L. -lmyl -no-pie
	gcc ${TEST_DIR}/x86/3_A5_quads4.o -o ${TEST_DIR}/exe/3_A5_quads4 -L. -lmyl -no-pie
	gcc ${TEST_DIR}/x86/3_A5_quads5.o -o ${TEST_DIR}/exe/3_A5_quads5 -L. -lmyl -no-pie
	gcc ${TEST_DIR}/x86/3_A5_quads1.o -o ${TEST_DIR}/exe/3_A5_quads1 -L. -lmyl -no-pie