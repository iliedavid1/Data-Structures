/*Copyright 2021 Ilie David */
#include "./header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    /* TODO */

    struct doubly_linked_list_t* linked_list = malloc(
        sizeof(struct doubly_linked_list_t));
    linked_list->size = 0;
    linked_list->data_size = data_size;
    linked_list->head = NULL;

    return linked_list;
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

    if (list->size == 1) {
        list->head = NULL;

        list->size--;
        return curr;
    }

    if (n == 0) {
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

/* Functie care elibereaza memoria folosita de scuturile fiecarei
 * planeta din galaxie
 */
void
shields_free(doubly_linked_list_t **list) {
    int i;
    struct dll_node_t *curr;
    doubly_linked_list_t *aux_list;
    curr = (*list)->head;

    for (i = 0; i < (int)(*list)->size; i++) {
        aux_list = ((struct planet*)curr->data)->shields;
        dll_free(&aux_list);
        curr = curr->next;
    }
}

/* Adaug numele, scuturile si initializez kill-urile pe 0 in structura
 * planeta, dupa care adaug planeta in lista care reprezinta galaxia
 */
void
add_planet(doubly_linked_list_t *galaxie, int ind_planet, char *name,
    int nr_shield) {
    struct planet new_planet;
    int j;

    if (ind_planet > (int)galaxie->size) {
                printf("Planet out of bounds!\n");
    } else {
        printf("The planet %s has joined the galaxy.\n", name);
        new_planet.shields = dll_create(sizeof(int));
        new_planet.kills = 0;
        strcpy(new_planet.name, name);
        for (j = 0; j < nr_shield; j++) {
            int a = 1;
            dll_add_nth_node(new_planet.shields, (unsigned int)j, &a);
        }
        dll_add_nth_node(galaxie, ind_planet, &new_planet);
    }
}

/* Sterg nodul care reprezinta planeta care trebuie sa fie
 * stearsa
 */
void
black_hole(doubly_linked_list_t *list, int n)
{
    dll_node_t *curr;
    doubly_linked_list_t *aux_list;

    curr = dll_remove_nth_node(list, n);
    aux_list = ((struct planet*)curr->data)->shields;
    dll_free(&aux_list);
    printf("The planet %s has been eaten by the vortex.\n",
        ((struct planet*)curr->data)->name);
    free(curr->data);
    free(curr);
}

/* Adaug variabila val la scutul caruia i se face upgrade
 */
void
upgrade(doubly_linked_list_t *list, int ind_planet, int ind_shield, int val)
{
    dll_node_t *curr;
    if (ind_planet >= (int)list->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        curr = dll_get_nth_node(list, (unsigned int)ind_planet);
        if (ind_shield >= (int)((struct planet*)curr->data)->shields->size) {
            printf("Shield out of bounds!\n");
            return;
        } else {
            curr = dll_get_nth_node(((struct planet*)curr->data)->shields,
                (unsigned int)ind_shield);
            *(int*)curr->data +=val;
        }
    }
}

/* Adaug pe ultima pozitie a listei de scuturi un nou nod
 * cu valoarea val
 */
void
expand(doubly_linked_list_t *list, int ind_planet, int val)
{
    dll_node_t *curr;
    if (ind_planet >= (int)list->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        curr = dll_get_nth_node(list, (unsigned int)ind_planet);
        dll_add_nth_node(((struct planet*)curr->data)->shields,
            ((struct planet*)curr->data)->shields->size, &val);
    }
}

/* Verific daca o planeta are mai mult de 4 scuturi si daca are
 * sterg scutul de pe pozitia ind_shield
 */
void
remove_shield(doubly_linked_list_t *list, int ind_planet, int ind_shield)
{
    dll_node_t *curr;
    if (ind_planet >= (int)list->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        curr = dll_get_nth_node(list, (unsigned int)ind_planet);
        if (ind_shield >= (int)((struct planet*)curr->data)->shields->size) {
            printf("Shield out of bounds!\n");
            return;
        } else if (((struct planet*)curr->data)->shields->size == 4) {
            printf("A planet cannot have less than 4 shields!\n");
            return;
        } else {
            curr = dll_remove_nth_node(((struct planet*)curr->data)->shields,
                (unsigned int)ind_shield);
            free(curr->data);
            free(curr);
        }
    }
}

/* Pentru a da rotate la lista de scuturi schimbam head-ul listei
 * cu un numar de unitati in functie de directie
 */
void
rotate(doubly_linked_list_t *list, int ind_planet, char sens, int unit)
{
    struct dll_node_t *curr;
    struct dll_node_t *curr2;
    if (ind_planet >= (int)list->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        if (sens != 'c' && sens != 't') {
            printf("Not a valid direction!\n");
            return;
        } else {
            curr = dll_get_nth_node(list, (unsigned int)ind_planet);
            unit = unit % ((struct planet*)curr->data)->shields->size;
            if (sens == 'c') {
                curr2 = dll_get_nth_node(((struct planet*)curr->data)->shields,
                    ((struct planet*)curr->data)->shields->size - unit);
                ((struct planet*)curr->data)->shields->head = curr2;
            } else {
                curr2 = dll_get_nth_node(((struct planet*)curr->data)->shields,
                    unit);
               ((struct planet*)curr->data)->shields->head = curr2;
            }
        }
    }
}

/* Folosesc cast la (struct planet*) pentru variabila data
 * din nodurile listei
 */
void
show(doubly_linked_list_t *list, int ind_planet)
{
    dll_node_t *curr;
    dll_node_t *curr2;
    int i;
    if (ind_planet >= (int)list->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        curr = dll_get_nth_node(list, (unsigned int)ind_planet);
        printf("NAME: %s\n",
            ((struct planet*)curr->data)->name);
        if (list->size == 1) {
            printf("CLOSEST: none\n");
        } else if (list->size == 2) {
            printf("CLOSEST: %s\n",
                ((struct planet*)curr->next->data)->name);
        } else {
            printf("CLOSEST: %s and %s\n",
                ((struct planet*)curr->prev->data)->name,
                ((struct planet*)curr->next->data)->name);
        }
        printf("SHIELDS: ");
        curr2 = ((struct planet*)curr->data)->shields->head;
        for (i = 0; i < (int)((struct planet*)curr->data)->shields->size; i++) {
            printf("%d ", *(int*)curr2->data);
            curr2 = curr2->next;
        }
        printf("\n");
        printf("KILLED: %d\n", ((struct planet*)curr->data)->kills);
    }
}

/* Scad valoarea scutului afectat cu 1 si verific daca a ajuns
 * la -1. Daca e -1 atunci sterg planeta si cresc valoarea kill-urilor
 * celeilalte planete cu 1
 */
void
collision(doubly_linked_list_t *list, int ind_planet, int ind_planet2)
{
    int ok = 0;
    doubly_linked_list_t *aux_list;
    dll_node_t *curr1;
    dll_node_t *curr2;
    dll_node_t *scut1;
    dll_node_t *scut2;
    if (ind_planet >= (int)list->size || ind_planet2 >= (int)list->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    curr1 = dll_get_nth_node(list, (unsigned int)ind_planet);
    curr2 = dll_get_nth_node(list, (unsigned int)ind_planet2);
    scut1 = dll_get_nth_node(((struct planet*)curr1->data)->shields,
        ((struct planet*)curr1->data)->shields->size / 4);
    *(int*)scut1->data -= 1;
    scut2 = dll_get_nth_node(((struct planet*)curr2->data)->shields,
        (((struct planet*)curr2->data)->shields->size / 4) * 3);
    *(int*)scut2->data -= 1;

    if (*(int*)scut1->data == -1) {
        printf("The planet %s has imploded.\n",
            ((struct planet*)curr1->data)->name);
        curr1 = dll_remove_nth_node(list, (unsigned int)ind_planet);
        aux_list = ((struct planet*)curr1->data)->shields;
        dll_free(&aux_list);
        free(curr1->data);
        free(curr1);
        ((struct planet*)curr2->data)->kills++;
        ok = 1;
    }
    if (*(int*)scut2->data == -1) {
        printf("The planet %s has imploded.\n",
            ((struct planet*)curr2->data)->name);
        if (ok == 1) {
            ind_planet--;
        }
        if (ind_planet == (int)(list->size - 1))
            ind_planet = -1;
        curr2 = dll_remove_nth_node(list, (unsigned int)(ind_planet + 1));
        aux_list = ((struct planet*)curr2->data)->shields;
        dll_free(&aux_list);
        free(curr2->data);
        free(curr2);
        if (ok == 0) {
            ((struct planet*)curr1->data)->kills++;
        }
    }
}
