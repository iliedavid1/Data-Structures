CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ansi
DEBUG=-g -ggdb -O0 -march=native

build: main

main: main.o functions.o
	$(CC) $(CFLAGS) $(DEBUG) main.o functions.o -o main

functions.o: header.h functions.c
	$(CC) $(CFLAGS) $(DEBUG) functions.c -c -o functions.o

main.o: main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -c -o main.o

run:
	./main

clean:
	rm *.o
	rm main

