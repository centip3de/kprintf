FLAGS=-Wno-incompatible-library-redeclaration
CC=gcc

.PHONY: all test clean

all: test

test: src/main.c src/kprintf.h
	$(CC) src/main.c src/kprintf.c -o test $(FLAGS)

clean:
	rm test
