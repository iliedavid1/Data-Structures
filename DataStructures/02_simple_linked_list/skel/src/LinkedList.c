#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

linked_list_t*
ll_create(unsigned int data_size)
{
    /* TODO */
    struct linked_list_t * linked_list = (struct linked_list_t*)malloc(sizeof(struct linked_list_t));

    linked_list->size = 0;
    linked_list->data_size = data_size;
    linked_list->head = NULL;

    return linked_list;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */
void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
    /* TODO */

    struct ll_node_t *curr;
    struct ll_node_t *node = (struct ll_node_t*)malloc(sizeof(struct ll_node_t));

    

    node->data = malloc(list->data_size);
    memcpy(node->data, new_data, list->data_size);

    curr = list->head;

    if (n >= list->size) {
    	node->next = NULL;

    	if (list->head == NULL) {
    		list->head = node;
    	} else {

    		while(curr->next != NULL) {
    			curr = curr->next;
    		}

    		curr->next = node;


    	}
    } else {

    	if (n == 0) {
    		node->next = list->head;
    		list->head = node;
    	} else {

    		int nr = 0;

    		while (nr != (int)(n - 1)) {
    			nr++;
    			curr = curr->next;
    		}

    		node->next = curr->next;
    		curr->next = node;
    	}
    }

    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    /* TODO */

	int nr = 0;
	struct ll_node_t *curr;
	struct ll_node_t *tmp;
	
	curr = list->head;

	if (n > list->size - 1)
		n = list->size - 1;

	if (n == 0) {
		list->head = curr->next;
		free(curr->data);
		free(curr);

		return curr;
	}

	while(nr != (int)(n - 1)) {
		nr++;
		curr = curr->next;
	}
	
	tmp = curr->next;
	curr->next = tmp->next;
	free(tmp->data);
	free(tmp);

	/* ??? */
	return tmp;

}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
ll_get_size(linked_list_t* list)
{
    /* TODO */
	unsigned int nr = 0;
    struct ll_node_t *curr;

    curr = list->head;

    while(curr != NULL) {
    	nr++;
    	curr = curr->next;
    }

    return nr;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void
ll_free(linked_list_t** pp_list)
{
    /* TODO */

    struct ll_node_t *curr;

    while((*pp_list)->head != NULL) {
    	curr = (*pp_list)->head;
    	(*pp_list)->head = (*pp_list)->head->next;
    	free(curr->data);
    	free(curr);
    }

    free(*(pp_list));
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
ll_print_int(linked_list_t* list)
{
    /* TODO */

    struct ll_node_t *curr;

    curr = list->head;

    while(curr != NULL) {
    	printf("%d ", *(int *)curr->data);
    	curr = curr->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void
ll_print_string(linked_list_t* list)
{
    /* TODO */

    struct ll_node_t *curr;

    curr = list->head;

    while(curr != NULL) {
    	printf("%s ", curr->data);
    	curr = curr->next;
    }

    printf("\n");
}
