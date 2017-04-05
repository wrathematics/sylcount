CC = gcc
CFLAGS=-O3 --std=c99  -Wall -pedantic

all: main test example

main:
	$(CC) $(CFLAGS) -o sylcount sylcount.c

example:
	$(CC) -o example example.c

clean:
	rm -f example test sylcount

.PHONY: test example main
