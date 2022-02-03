/* Copyright 2021 <Ilie David> */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "load_balancer.h"
#include "server.h"
#include "Hashtable.h"
#include "LinkedList.h"
#include "CircularDoublyLinkedList.h"

#define NR_SERVER 300000

struct elem_ring {
    unsigned int hash;
    int server_id;
};

struct load_balancer {
    doubly_linked_list_t *hashring;
    server_memory **servers;
};

unsigned int hash_function_servers(void *a) {
    unsigned int uint_a = *((unsigned int *)a);

    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = (uint_a >> 16u) ^ uint_a;
    return uint_a;
}

unsigned int hash_function_key(void *a) {
    unsigned char *puchar_a = (unsigned char *) a;
    unsigned int hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c;

    return hash;
}

/*Aloc memorie pentru loadbalancer si initializez fiecare elem din vectorul
 *de pointeri la servere cu NULL, pentru a-mi da seama ce sa dealoc la sfarsit
 */
load_balancer* init_load_balancer() {
    load_balancer *main_server = (load_balancer *)malloc(sizeof(load_balancer));
    int i;
    main_server->servers = malloc(NR_SERVER * sizeof(server_memory *));
    main_server->hashring = dll_create(sizeof(elem_ring));

    for (i = 0; i < NR_SERVER; i++) {
        main_server->servers[i] = NULL;
    }
    return main_server;
}

/*Verific daca hash-ul cheii este mai mare decat ultimul hash din hashring, in
 *cazul in care stochez elementul pe primul server din hashring, iar daca nu este,
 *caut unde ar trebui stocat elementul in hashring
 */
void loader_store(load_balancer* main, char* key, char* value, int* server_id) {
    dll_node_t *curr = main->hashring->head;
    unsigned int hash_key = hash_function_key(key);
    if (hash_key >= ((struct elem_ring *)curr->prev->data)->hash) {
        *server_id = ((struct elem_ring *)curr->data)->server_id;
        server_store(main->servers[*server_id], key, value);
        return;
    }
    while (curr != NULL) {
        if (hash_key < ((struct elem_ring *)curr->data)->hash) {
            *server_id = ((struct elem_ring *)curr->data)->server_id;
            break;
        }
        curr = curr->next;
    }
    server_store(main->servers[*server_id], key, value);
}

/*Caut pe ultima pozitie si, in cazul in care nu gasesc cheia, caut in
 *hashring in pozitie in pozitie
 */
char* loader_retrieve(load_balancer* main, char* key, int* server_id) {
    char *value = NULL;
    dll_node_t *curr = main->hashring->head;
    unsigned int hash_key = hash_function_key(key);
    if (hash_key > ((struct elem_ring *)curr->prev->data)->hash) {
        *server_id = ((struct elem_ring *)curr->data)->server_id;
        value = server_retrieve(main->servers[*server_id], key);
        return value;
    }
    while (curr != NULL) {
        if (hash_key < ((struct elem_ring *)curr->data)->hash) {
            *server_id = ((struct elem_ring *)curr->data)->server_id;
            value = server_retrieve(main->servers[*server_id], key);
            return value;
        }
        curr = curr->next;
    }
    return NULL;
}

void loader_add_server(load_balancer* main, int server_id) {
    server_memory *new_server = init_server_memory();
    new_server->id = server_id;
    int i, j;
    main->servers[server_id] = new_server;
    elem_ring data;
    data.hash = hash_function_servers(&server_id);
    data.server_id = server_id;
    dll_node_t *curr = main->hashring->head;

    for (i = 0; i < 3; i++) {
        /*adaugarea serverelor in hshring*/
        curr = main->hashring->head;
        int replica = i * 100000 + server_id;
        data.hash = hash_function_servers(&replica);
        unsigned int k = 0;
        int ok = 0;
        if (curr == NULL) {
            dll_add_nth_node(main->hashring, 0, &data);
            continue;
        }
        if (data.hash > ((struct elem_ring *)curr->prev->data)->hash) {
            dll_add_nth_node(main->hashring, main->hashring->size, &data);
            k = 0;
            ok = 1;
        }
        while (ok == 0) {
            if (data.hash < ((struct elem_ring *)curr->data)->hash) {
                dll_add_nth_node(main->hashring, k, &data);
                k++;
                break;
            }
            k++;
            curr = curr->next;
        }
        /*remaparea elementelor in servere*/
        curr = dll_get_nth_node(main->hashring, k);
        unsigned int hash_prev, hash_next;
        hash_prev = ((struct elem_ring *)curr->prev->prev->data)->hash;
        hash_next = ((struct elem_ring *)curr->prev->data)->hash;
        int id_srv = ((struct elem_ring *)curr->data)->server_id;

        if (server_id == id_srv) {
            continue;
        }
        for (j = 0; j < (int)main->servers[id_srv]->hashtable->hmax; j++) {
            if (main->servers[id_srv]->hashtable->buckets[j] == NULL) {
                continue;
            }
            hashtable_t *ht = main->servers[id_srv]->hashtable;
            ll_node_t *curr2 = ht->buckets[j]->head;
            while (curr2 != NULL) {
                char *key = (char *)((struct info *)curr2->data)->key;
                char *value = (char *)((struct info *)curr2->data)->value;
                /*in cazul in care se adauga un server pe prima pozitie
                 *(k == 1), atunci cautam elemente cu hash ul mai mare decat
                 *hash-ul ultimului server sau elemente cu hash-ul mai mic
                 *decat hash-ul primului server */
                if (k == 1 &&
                    hash_function_key(key) > hash_prev) {
                    server_store(main->servers[server_id], key, value);
                    curr2 = curr2->next;
                    server_remove(main->servers[id_srv], key);
                } else if (k == 1 &&
                    hash_function_key(key) < hash_next) {
                    server_store(main->servers[server_id], key, value);
                    curr2 = curr2->next;
                    server_remove(main->servers[id_srv], key);
                } else if (hash_function_key(key) < hash_next &&
                    hash_function_key(key) > hash_prev) {
                    server_store(main->servers[server_id], key, value);
                    curr2 = curr2->next;
                    server_remove(main->servers[id_srv], key);
                } else {
                    curr2 = curr2->next;
                }
            }
        }
    }
}

void loader_remove_server(load_balancer* main, int server_id) {
    dll_node_t *curr = main->hashring->head;
    int size = main->hashring->size;
    /*cautam serverul in hashring si il eliminam din acesta*/
    while (size > 0) {
        if (((struct elem_ring *)curr->data)->server_id == server_id) {
            curr = curr->next;
            dll_node_t *node = dll_remove_nth_node(main->hashring,
                main->hashring->size - size);
            free(node->data);
            free(node);
            size--;
        } else {
            curr = curr->next;
            size--;
        }
    }
    /*redistribuim elementele pe care le stoca serverul pe care il stergem*/
    for (int i = 0; i < (int)main->servers[server_id]->hashtable->hmax; i++) {
        if (main->servers[server_id]->hashtable->buckets[i] == NULL) {
            continue;
        }
        hashtable_t *ht = main->servers[server_id]->hashtable;
        ll_node_t *curr2 = ht->buckets[i]->head;
        while (curr2 != NULL) {
            int id = 0;
            loader_store(main, ((struct info *)curr2->data)->key,
                ((struct info *)curr2->data)->value, &id);
            curr2 = curr2->next;
        }
    }
    free_server_memory(main->servers[server_id]);
    main->servers[server_id] = NULL;
}

void free_load_balancer(load_balancer* main) {
    dll_free(&main->hashring);
    /*pentru fiecare server pe care l-am alocat
     *apelam functia de dealocare a memoriei serverelor
     */
    for (int i = 0; i < NR_SERVER; i++) {
        if (main->servers[i] != NULL) {
            free_server_memory(main->servers[i]);
        }
    }
    free(main->servers);
    free(main);
}
