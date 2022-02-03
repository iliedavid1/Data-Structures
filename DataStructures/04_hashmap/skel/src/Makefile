CC=clang
CFLAGS=-Wall -Wextra -pedantic -ansi
DEBUG=-g -ggdb -O0 -march=native

build: problema_2

problema_2: problema_2.o Hashtable_unlinked.o LinkedList.o
	$(CC) $(CFLAGS) $(DEBUG) problema_2.o Hashtable_unlinked.o LinkedList.o -o problema_2


Hashtable_unlinked.o: Hashtable.h Hashtable.c
	$(CC) $(CFLAGS) $(DEBUG) Hashtable.c -c -o Hashtable_unlinked.o

LinkedList.o: LinkedList.h LinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) LinkedList.c -c -o LinkedList.o

problema_2.o: problema_2.c
	$(CC) $(CFLAGS) $(DEBUG) problema_2.c -c -o problema_2.o

run:
	./problema_2

clean:
	rm -f src/*.o
	rm -f problema_2

