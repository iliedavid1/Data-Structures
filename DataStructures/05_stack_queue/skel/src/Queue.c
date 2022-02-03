#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "utils.h"

queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	/* TODO */
	queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
	DIE(!queue, "malloc queue");
	queue->max_size = max_size;
	queue->size = 0;
	queue->data_size = data_size;
	queue->read_idx = 0;
	queue->write_idx = 0;
	queue->buff = malloc(max_size * data_size);
	return queue;
}

unsigned int
q_get_size(queue_t *q)
{
	/* TODO */
	return q->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
q_is_empty(queue_t *q)
{
	/* TODO */
	if (q->size == 0) {
		return 1;
	} else {
		return 0;
	}
}

void *
q_front(queue_t *q)
{
	/* TODO */
	if (q_is_empty(q) == 0) {
		return (char *)q->buff + q->read_idx * q->data_size;
	}
	return NULL;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_dequeue(queue_t *q)
{
	/* TODO */
	/* verific daca queue-ul este gol */
	if (q_is_empty(q) == 1)
		return false;
	q->read_idx++;
	q->read_idx = q->read_idx % q->max_size;
	q->size--;
	return true;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_enqueue(queue_t *q, void *new_data)
{
	/* TODO */
	/* nu mai pot adauga daca queue-ul este deja plin */
	if (q_get_size(q) == q->max_size)
		return false;
	memcpy((char *)q->buff + q->write_idx * q->data_size, new_data, q->data_size);
	q->write_idx++;
	q->write_idx = q->write_idx % q->max_size;
	q->size++;
	return true;
}

void
q_clear(queue_t *q)
{
	/* TODO */
	int n = q->size;
	while (n > 0) {
		q_dequeue(q);
		n--;
	}
}

void
q_free(queue_t *q)
{
	/* TODO */
	free(q->buff);
	free(q);
}
