build:
	bison 3_A3.y --defines=3_A3.tab.h -o 3_A3.tab.c
	flex -o lex.yy.c 3_A3.l
	gcc -o parser lex.yy.c 3_A3.tab.c 3_A3.c -lfl -Werror

clean-head:
	rm -f lex.yy.c 3_A3.tab.c 3_A3.tab.h

clean-out: clean-head
	rm -f parser

clean-all: clean-out
	rm -f 3_A3_nc_output.txt

test: build
	./parser < 3_A3.nc

test-out: build
	./parser < 3_A3.nc > 3_A3_nc_output.txt

test-sample: build
	./parser < ./sample_output_A3/bubble_sort.nc > ./output/bubble_sort.output
	./parser < ./sample_output_A3/corecursive_fibonacci.nc > ./output/corecursive_fibonacci.output
	./parser < ./sample_output_A3/error_test.nc > ./output/error_test.output
	python3 test-cases.py > ./output/results.txt

conflict:
	bison -d 3_A3.y -t -Wcounterexamples
	flex -o lex.yy.c 3_A3.l
	gcc -o parser lex.yy.c 3_A3.tab.c 3_A3.c -lfl -Werror
	./parser < 3_A3.nc