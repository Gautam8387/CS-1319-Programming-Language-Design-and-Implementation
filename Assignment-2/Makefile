all:
	flex -o 3_A2.yy.c 3_A2.l
	gcc 3_A2.yy.c 3_A2.c -ll -o 3_A2.out
	./3_A2.out < 3_A2.nc

clean:
	rm 3_A2.out 3_A2.yy.c
