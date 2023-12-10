.SUFFIXES: 
GROUP = 3_A5
TEST_DIR = A5_Tests
EXTRA_DIR = $(TEST_DIR)/extra_cred

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
	
	./compiler 2 ${TEST_DIR}/test2.nc
	mv 3_A5_quads2.out ${TEST_DIR}/tac && mv 3_A5_quads2.asm ${TEST_DIR}/x86
	as ${TEST_DIR}/x86/3_A5_quads2.asm -o ${TEST_DIR}/x86/3_A5_quads2.o
	gcc ${TEST_DIR}/x86/3_A5_quads2.o -o ${TEST_DIR}/exe/3_A5_quads2 -L. -lmyl -no-pie
	
	./compiler 2 ${TEST_DIR}/test3.nc
	mv 3_A5_quads3.out ${TEST_DIR}/tac && mv 3_A5_quads3.asm ${TEST_DIR}/x86
	as ${TEST_DIR}/x86/3_A5_quads3.asm -o ${TEST_DIR}/x86/3_A5_quads3.o
	gcc ${TEST_DIR}/x86/3_A5_quads3.o -o ${TEST_DIR}/exe/3_A5_quads3 -L. -lmyl -no-pie
	
	./compiler 2 ${TEST_DIR}/test4.nc
	mv 3_A5_quads4.out ${TEST_DIR}/tac && mv 3_A5_quads4.asm ${TEST_DIR}/x86
	as ${TEST_DIR}/x86/3_A5_quads4.asm -o ${TEST_DIR}/x86/3_A5_quads4.o
	gcc ${TEST_DIR}/x86/3_A5_quads4.o -o ${TEST_DIR}/exe/3_A5_quads4 -L. -lmyl -no-pie

	./compiler 2 ${TEST_DIR}/test5.nc
	mv 3_A5_quads5.out ${TEST_DIR}/tac && mv 3_A5_quads5.asm ${TEST_DIR}/x86
	as ${TEST_DIR}/x86/3_A5_quads5.asm -o ${TEST_DIR}/x86/3_A5_quads5.o
	gcc ${TEST_DIR}/x86/3_A5_quads5.o -o ${TEST_DIR}/exe/3_A5_quads5 -L. -lmyl -no-pie
		
	./compiler 2 ${TEST_DIR}/test7.nc
	mv 3_A5_quads7.out ${TEST_DIR}/tac && mv 3_A5_quads7.asm ${TEST_DIR}/x86
	as ${TEST_DIR}/x86/3_A5_quads7.asm -o ${TEST_DIR}/x86/3_A5_quads7.o
	gcc ${TEST_DIR}/x86/3_A5_quads7.o -o ${TEST_DIR}/exe/3_A5_quads7 -L. -lmyl -no-pie

	./compiler 2 ${TEST_DIR}/test1.nc
	mv 3_A5_quads1.out ${TEST_DIR}/tac && mv 3_A5_quads1.asm ${TEST_DIR}/x86
	as ${TEST_DIR}/x86/3_A5_quads1.asm -o ${TEST_DIR}/x86/3_A5_quads1.o

	./compiler 2 ${TEST_DIR}/test6.nc
	mv 3_A5_quads6.out ${TEST_DIR}/tac && mv 3_A5_quads6.asm ${TEST_DIR}/x86
	as ${TEST_DIR}/x86/3_A5_quads6.asm -o ${TEST_DIR}/x86/3_A5_quads6.o
	gcc ${TEST_DIR}/x86/3_A5_quads6.o -o ${TEST_DIR}/exe/3_A5_quads6 -L. -lmyl -no-pie
	
	gcc ${TEST_DIR}/x86/3_A5_quads1.o -o ${TEST_DIR}/exe/3_A5_quads1 -L. -lmyl -no-pie

test-extra: compiler
	rm -rf ${EXTRA_DIR}/x86 && rm -rf ${EXTRA_DIR}/tac && rm -rf ${EXTRA_DIR}/exe
	mkdir ${EXTRA_DIR}/x86 && mkdir ${EXTRA_DIR}/tac && mkdir ${EXTRA_DIR}/exe
	
	./compiler 2 ${EXTRA_DIR}/ec_1.nc
	mv 3_A5_quads1.out ${EXTRA_DIR}/tac && mv 3_A5_quads1.asm ${EXTRA_DIR}/x86
	as ${EXTRA_DIR}/x86/3_A5_quads1.asm -o ${EXTRA_DIR}/x86/3_A5_quads1.o
	gcc ${EXTRA_DIR}/x86/3_A5_quads1.o -o ${EXTRA_DIR}/exe/3_A5_quads1 -L. -lmyl -no-pie
	
	./compiler 2 ${EXTRA_DIR}/ec_3.nc
	mv 3_A5_quads3.out ${EXTRA_DIR}/tac && mv 3_A5_quads3.asm ${EXTRA_DIR}/x86
	as ${EXTRA_DIR}/x86/3_A5_quads3.asm -o ${EXTRA_DIR}/x86/3_A5_quads3.o
	gcc ${EXTRA_DIR}/x86/3_A5_quads3.o -o ${EXTRA_DIR}/exe/3_A5_quads3 -L. -lmyl -no-pie
	
	./compiler 2 ${EXTRA_DIR}/ec_4.nc
	mv 3_A5_quads4.out ${EXTRA_DIR}/tac && mv 3_A5_quads4.asm ${EXTRA_DIR}/x86
	as ${EXTRA_DIR}/x86/3_A5_quads4.asm -o ${EXTRA_DIR}/x86/3_A5_quads4.o
	gcc ${EXTRA_DIR}/x86/3_A5_quads4.o -o ${EXTRA_DIR}/exe/3_A5_quads4 -L. -lmyl -no-pie
	
	./compiler 2 ${EXTRA_DIR}/ec_5.nc
	mv 3_A5_quads5.out ${EXTRA_DIR}/tac && mv 3_A5_quads5.asm ${EXTRA_DIR}/x86
	as ${EXTRA_DIR}/x86/3_A5_quads5.asm -o ${EXTRA_DIR}/x86/3_A5_quads5.o
	gcc ${EXTRA_DIR}/x86/3_A5_quads5.o -o ${EXTRA_DIR}/exe/3_A5_quads5 -L. -lmyl -no-pie
	
	./compiler 2 ${EXTRA_DIR}/ec_6.nc
	mv 3_A5_quads6.out ${EXTRA_DIR}/tac && mv 3_A5_quads6.asm ${EXTRA_DIR}/x86
	as ${EXTRA_DIR}/x86/3_A5_quads6.asm -o ${EXTRA_DIR}/x86/3_A5_quads6.o
	gcc ${EXTRA_DIR}/x86/3_A5_quads6.o -o ${EXTRA_DIR}/exe/3_A5_quads6 -L. -lmyl -no-pie
	
	./compiler 2 ${EXTRA_DIR}/ec_7.nc
	mv 3_A5_quads7.out ${EXTRA_DIR}/tac && mv 3_A5_quads7.asm ${EXTRA_DIR}/x86
	as ${EXTRA_DIR}/x86/3_A5_quads7.asm -o ${EXTRA_DIR}/x86/3_A5_quads7.o
	gcc ${EXTRA_DIR}/x86/3_A5_quads7.o -o ${EXTRA_DIR}/exe/3_A5_quads7 -L. -lmyl -no-pie
	
	./compiler 2 ${EXTRA_DIR}/ec_8.nc
	mv 3_A5_quads8.out ${EXTRA_DIR}/tac && mv 3_A5_quads8.asm ${EXTRA_DIR}/x86
	as ${EXTRA_DIR}/x86/3_A5_quads8.asm -o ${EXTRA_DIR}/x86/3_A5_quads8.o
	gcc ${EXTRA_DIR}/x86/3_A5_quads8.o -o ${EXTRA_DIR}/exe/3_A5_quads8 -L. -lmyl -no-pie