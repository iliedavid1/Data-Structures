CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
LOAD=load_balancer
SERVER=server
HASHTABLE=Hashtable
LINKLIST=LinkedList
CIRCULARLINKEDLIST=CircularDoublyLinkedList

.PHONY: build clean

build: tema2

tema2: main.o $(CIRCULARLINKEDLIST).o $(LOAD).o $(SERVER).o $(HASHTABLE).o $(LINKLIST).o
	$(CC) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) $^ -c

$(CIRCULARLINKEDLIST).o: $(CIRCULARLINKEDLIST).c $(CIRCULARLINKEDLIST).h
	$(CC) $(CFLAGS) $^ -c

$(HASHTABLE).o: $(HASHTABLE).c $(HASHTABLE).h
	$(CC) $(CFLAGS) $^ -c

$(SERVER).o: $(SERVER).c $(SERVER).h
	$(CC) $(CFLAGS) $^ -c

$(LOAD).o: $(LOAD).c $(LOAD).h
	$(CC) $(CFLAGS) $^ -c

$(LINKLIST).o: $(LINKLIST).c $(LINKLIST).h
	$(CC) $(CFLAGS) $^ -c

run:
	valgrind --leak-check=full --track-origins=yes ./tema2 in/test6.in
clean:
	rm -f *.o tema2 *.h.gch
