/* Copyright 2021 <Ilie David> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "Hashtable.h"
#include "LinkedList.h"

unsigned int hash(void *a) {
    unsigned char *puchar_a = (unsigned char *) a;
    unsigned int hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c;

    return hash;
}

server_memory* init_server_memory() {
	/* TODO. */
	server_memory *server = (server_memory *)malloc(sizeof(server_memory));
	server->hashtable = ht_create(3000, hash, compare_function_strings);
	server->id = -1;
	return server;
}

/*Stochez elementele in dictionarul serverului*/
void server_store(server_memory* server, char* key, char* value) {
	/* TODO. */
	unsigned int key_size = strlen(key) + 1;
	unsigned int value_size = strlen(value) + 1;
	ht_put(server->hashtable, key, key_size, value, value_size);
}

void server_remove(server_memory* server, char* key) {
	/* TODO. */
	ht_remove_entry(server->hashtable, key);
}

char* server_retrieve(server_memory* server, char* key) {
	/* TODO. */
	return (char *)ht_get(server->hashtable, key);
}

void free_server_memory(server_memory* server) {
	/* TODO. */
	ht_free(server->hashtable);
	free(server);
}
