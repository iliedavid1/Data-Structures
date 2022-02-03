/*"Copyright 2021 Ilie David"*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    /* TODO */
    unsigned int size_of = sizeof(struct doubly_linked_list_t);
    struct doubly_linked_list_t* linked_list = malloc(size_of);
    linked_list->size = 0;
    linked_list->data_size = data_size;
    linked_list->head = NULL;

    return linked_list;
}
/*
 * Functie care sterge elementul din mijlocul unei liste dublu inlantuite fara
 * sa se cunoasca numarul de elemente, parcurgand-o o singura data
 */
void
dll_remove_mid(doubly_linked_list_t** list)
{
    struct dll_node_t *slow;
    struct dll_node_t *fast;

    slow = (*list)->head;
    fast = (*list)->head;

    if (slow->next == slow) {
        free(slow->data);
        free(slow);
        (*list)->head = NULL;
        (*list)->size--;

        return;
    } else if (slow->next->next == slow) {
        fast = slow->next;
        fast->next = fast;
        fast->prev = fast;
        (*list)->head = fast;
        free(slow->data);
        free(slow);
        (*list)->size--;

        return;
    }

    while (fast->next != (*list)->head && fast->next->next != (*list)->head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    fast = slow->prev;
    fast->next = slow->next;
    slow->next->prev = fast;

    free(slow->data);
    free(slow);

    (*list)->size--;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    /* TODO */
    int i;
    struct dll_node_t *curr;

    if (n > list->size - 1) {
        n = n % list->size;
    }

    curr = list->head;

    for (i = 0; i < (int)n; i++) {
        curr = curr->next;
    }

    return curr;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    /* TODO */

    struct dll_node_t *curr;
    struct dll_node_t *next = (struct dll_node_t*)malloc(sizeof(dll_node_t));

    next->data = malloc(list->data_size);
    memcpy(next->data, data, list->data_size);

    curr = list->head;

    if (n >= list->size) {
        next->next = list->head;

        if (list->head == NULL) {
            list->head = next;
            next->prev = list->head;
            next->next = list->head;
        } else {
            list->head->prev->next = next;
            next->prev = list->head->prev;
            list->head->prev = next;
        }
    } else {
        if (n == 0) {
            next->next = list->head;
            next->prev = list->head->prev;
            list->head->prev->next = next;
            list->head->prev = next;
            list->head = next;
        } else {
            int nr = 0;

            while (nr != (int)(n - 1)) {
                nr++;
                curr = curr->next;
            }

            next->next = curr->next;
            next->prev = curr;
            curr->next->prev = next;
            curr->next = next;
        }
    }

    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    /* TODO */
    int nr = 0;
    struct dll_node_t *curr;
    struct dll_node_t *aux;

    curr = list->head;

    if (n == 0 || list->size == 1) {
        list->head->prev->next = curr->next;
        curr->next->prev = list->head->prev;
        list->head = curr->next;

        list->size--;

        return curr;
    }

    if (n > list->size - 1)
        n = list->size - 1;

    while (nr != (int)(n - 1)) {
        nr++;
        curr = curr->next;
    }

    aux = curr->next;
    curr->next = aux->next;
    aux->next->prev = curr;

    list->size--;

    return aux;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    /* TODO */

    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    /* TODO */

    struct dll_node_t *curr;

    if ((*pp_list)->size == 0) {
        free((*pp_list));
        *pp_list = NULL;
    } else {
        curr = (*pp_list)->head->next;
        while (curr && curr != (*pp_list)->head) {
            struct dll_node_t *tmp = curr;
            curr = curr->next;
            free(tmp->data);
            free(tmp);
        }

        free((*pp_list)->head->data);
        free((*pp_list)->head);
        free((*pp_list));
        *pp_list = NULL;
    }
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
    /* TODO */
    int i;
    struct dll_node_t *curr;

    curr = list->head;

    for (i = 0; i < (int)list->size; i++) {
        printf("%d ", ((struct elem_ring1 *)curr->data)->server_id);
        curr = curr->next;
    }
    printf("\n");
    for (i = 0; i < (int)list->size; i++) {
        printf("%u ", ((struct elem_ring1 *)curr->data)->hash);
        curr = curr->next;
    }
    printf("\n");
}
/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_left_circular(dll_node_t* start)
{
    /* TODO */

    struct dll_node_t *curr;

    curr = start;

    while (curr->prev != start) {
        printf("%d ", *(int *)curr->data);
        curr = curr->prev;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_right_circular(dll_node_t* start)
{
    /* TODO */

    struct dll_node_t *curr;

    curr = start;

    while (curr->next != start) {
        printf("%d ", *(int *)curr->data);
        curr = curr->next;
    }
    printf("\n");
}
