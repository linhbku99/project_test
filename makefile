all: lab6.c
	gcc -o lab6 lab6.c -lpthread
clearn:
	rm -f lab6
