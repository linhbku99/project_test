all: test1.c test2.c test3.c
	gcc -o test1 test1.c -lpthread
	gcc -o test2 test2.c -lpthread
	gcc -o test3 test3.c -lpthread
clearn:
	rm -f test1 test2 test3
