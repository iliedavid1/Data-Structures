/*Copyright 2021 Ilie David */
#ifndef HEADER_H_
#define HEADER_H_

typedef struct dll_node_t dll_node_t;
struct dll_node_t
{
    void* data;
    dll_node_t *prev, *next;
};

typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t
{
    dll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};

struct planet
{
	doubly_linked_list_t *shields;
	char name[21];
	int kills;
};

/*
 * Acestea sunt functiile pe care trebuie sa le implementam.
 * Implementarea acestora se va face in LinkedList.c .
 */
void
dll_remove_mid(doubly_linked_list_t** list);

doubly_linked_list_t*
dll_create(unsigned int data_size);

dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n);

void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data);

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n);

unsigned int
dll_get_size(doubly_linked_list_t* list);

void
dll_free(doubly_linked_list_t** pp_list);

void
dll_print_int_list(doubly_linked_list_t* list);

void
dll_print_string_list(doubly_linked_list_t* list);

void
dll_print_ints_left_circular(dll_node_t* start);

void
shields_free(doubly_linked_list_t **list);

void
upgrade(doubly_linked_list_t *list, int ind_planet, int ind_shield, int val);

void
expand(doubly_linked_list_t *list, int ind_planet, int val);

void
rotate(doubly_linked_list_t *list, int ind_planet, char sens, int unit);

void
show(doubly_linked_list_t *list, int ind_planet);

void
black_hole(doubly_linked_list_t *list, int n);

void
collision(doubly_linked_list_t *list, int ind_planet, int ind_planet2);

void
remove_shield(doubly_linked_list_t *list, int ind_planet, int ind_shield);

void
add_planet(doubly_linked_list_t *galaxie, int ind_planet, char *name,
    int nr_shield);

void
dll_print_ints_right_circular(dll_node_t* start);
#endif  /* HEADER_H_ */
