#include <stdlib.h>

#include "Stack.h"
#include "utils.h"

stack_t *
st_create(unsigned int data_size)
{
	/* TODO */
	stack_t *stack = (stack_t*)malloc(sizeof(stack_t));
	DIE(!stack, "malloc stack");
	stack->list = ll_create(data_size);
	return stack;
}

unsigned int
st_get_size(stack_t *st)
{
	/* TODO */
	return st->list->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
st_is_empty(stack_t *st)
{
	/* TODO */
	if (st->list->size == 0) {
		return 1;
	} else
		return 0;
}

void *
st_peek(stack_t *st)
{
	/* TODO */
	if (st == NULL)
		return NULL;
	return st->list->head->data;
}

void
st_pop(stack_t *st)
{
	/* TODO */
	ll_node_t *elem = ll_remove_nth_node(st->list, 0);
	free(elem->data);
	free(elem);
}

void
st_push(stack_t *st, void *new_data)
{
	/* TODO */
	ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t *st)
{
	/* TODO */
	int nr = st->list->size;
	while (nr > 0) {
		st_pop(st);
		nr--;
		//printf("%d ", st->list->size);
	}
	//printf("\n");
}

void
st_free(stack_t *st)
{
	/* TODO */
	st_clear(st);
	free(st->list);
	free(st);
}
