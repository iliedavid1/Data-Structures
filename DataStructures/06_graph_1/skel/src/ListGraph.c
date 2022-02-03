#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"

list_graph_t*
lg_create(int nodes)
{
	/* TODO */
	list_graph_t *graph = (list_graph_t*)malloc(sizeof(list_graph_t));

	graph->nodes = nodes;
	graph->neighbours = (linked_list_t**)malloc(nodes * sizeof(linked_list_t*));

	for (int i = 0; i < nodes; i++) {
		graph->neighbours[i] = ll_create(sizeof(int));
	}

	return graph;
}

void
lg_add_edge(list_graph_t* graph, int src, int dest)
{
	/* TODO */
	ll_node_t *curr = graph->neighbours[src]->head;

	while (curr != NULL) {
		if (*(int*)curr->data == dest) {
			return;
		}
		curr = curr->next;
	}
	ll_add_nth_node(graph->neighbours[src], graph->neighbours[src]->size,
		&dest);
}

int
lg_has_edge(list_graph_t* graph, int src, int dest)
{
	/* TODO */
	ll_node_t *curr = graph->neighbours[src]->head;

	while (curr != NULL) {
		if (*(int*)curr->data == dest)
			return 1;
		curr = curr->next;
	}

	return 0;
}

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node)
{
	/* TODO */
	return graph->neighbours[node];
}

void
lg_remove_edge(list_graph_t* graph, int src, int dest)
{
	/* TODO */
	ll_node_t *curr = graph->neighbours[src]->head;
	int nr = 0;

	while (*(int*)curr->data != dest) {
		curr = curr->next;
		nr++;
	}
	curr = ll_remove_nth_node(graph->neighbours[src], nr);
	free(curr->data);
	free(curr);
}

void
lg_free(list_graph_t* graph)
{
	/* TODO */

	for (int i = 0; i < graph->nodes; i++) {
		linked_list_t *nodes = graph->neighbours[i];
		ll_free(&nodes);
	}
	free(graph->neighbours);
	free(graph);
}