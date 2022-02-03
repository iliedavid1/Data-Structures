#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"


#define MAX_NODES	100
#define INF		0x3f3f3f3f

/**
 * Adaugati nodurile componentei conexe curente in lista component. 
 */
static void
dfs_connected_comps(
	list_graph_t *lg,
	int node,
	int *visited,
	linked_list_t *component
) {
	/* TODO */
}

static linked_list_t **
connected_components(list_graph_t *lg, int *visited, unsigned int *num_comp)
{
	linked_list_t **comps = malloc(lg->nodes * sizeof(*comps));
	DIE(!comps, "malloc comps failed");

	/* TODO: adaugati fiecare componenta conexa ca o noua lista in comps */

	return comps;
}

static void
dfs_topo_sort(list_graph_t *lg, int node, int *visited, linked_list_t *sorted)
{
	/* TODO */
	ll_node_t *curr;
	stack_t *st = st_create(sizeof(int));

	//int time = 0;
	visited[node] = 1;

	st_push(st, &node);

	while(st_is_empty(st) != 1) {
		int v = *(int*)st_peek(st);
		curr = lg->neighbors[v]->head;
		int ok = 0;
		if (curr == NULL) {
			ok = 1;
		}
		while (curr != NULL && visited[*(int*)curr->data] == 1) {
			if (curr->next == NULL) {
				if (visited[*(int*)curr->data] == 1) {
					ok = 1;
					break;
				}
			}
			if (curr == NULL) {
				ok = 1;
				break;
			}
			curr = curr->next;
		}
		if (ok == 0) {
			//time++;
			visited[*(int*)curr->data] = 1;
			//t_desc[*(int*)curr->data] = time;
			//printf("%d ", *(int*)curr->data);
			st_push(st, curr->data);
		} else {
			//time++;
			//t_tin[v] = time;
			ll_add_nth_node(sorted, 0, &v);
			st_pop(st);
		}
	}
	st_free(st);
}

static linked_list_t *
topo_sort(list_graph_t *lg, int *visited)
{
	linked_list_t *sorted = ll_create(sizeof(int));
	
	/* TODO: adaugati nodurile in lista sorted, in ordinea corecta */
	for (int i = 0; i < lg->nodes; i++) {
		if (visited[i] == 0)
			dfs_topo_sort(lg, i, visited, sorted);
	}

	return sorted;
}

static void
min_path(list_graph_t *lg, int start, int *dist)
{
	/* TODO */
}

static int
check_bipartite(list_graph_t *lg, int *color)
{
	/* TODO: multimile vor avea culorile 1, respectiv 2 */
	ll_node_t *curr;
	queue_t *q = q_create(sizeof(int), lg->nodes);

	for (int i = 0; i < lg->nodes; i++) {
		color[i] = 0;
	}
	for (int i = 0; i < lg->nodes; i++) {
		if (lg->neighbors[i]->head != NULL) {
			color[i] = 1;
			q_enqueue(q, &i);
			break;
		}
	}

	while (q_is_empty(q) != 1) {
		int v = *(int*)q_front(q);
		q_dequeue(q);
		curr = lg->neighbors[v]->head;
		while (curr != NULL) {
			if (color[*(int*)curr->data] == 0) {
				if (color[v] == 1)
					color[*(int*)curr->data] = 2;
				else
					color[*(int*)curr->data] = 1;
				q_enqueue(q, curr->data);
			} else if (color[v] == color[*(int*)curr->data]) {
				q_free(q);
				return 0;
			}
			curr = curr->next;
		}
	}
	q_free(q);
	return 1;
}

static void
test_connected_comp(void)
{
	unsigned int num_comps, i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t **comps;

	printf("UNDIRECTED graph for the connected components problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	comps = connected_components(lg, visited, &num_comps);

	printf("Found %d connected components:\n", num_comps);
	for (i = 0; i != num_comps; ++i) {
		ll_print_int(comps[i]);
		ll_free(comps + i);
	}
	printf("\n");

	free(comps);
	lg_free(lg);
}

static void
test_topo_sort(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t *sorted;

	printf("DIRECTED graph for the topological sort problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
	}

	sorted = topo_sort(lg, visited);

	printf("Topologically sorted nodes:\n");
	ll_print_int(sorted);
	printf("\n");

	ll_free(&sorted);
	lg_free(lg);
}

static void
test_min_dist(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int dist[MAX_NODES] = {0};
	list_graph_t *lg;

	printf("UNDIRECTED graph for the minimum distance problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	for (i = 0; i != nodes; ++i)
		dist[i] = INF;

	min_path(lg, 0, dist);

	printf("Minimum distances to node 0:\n");
	for (i = 0; i != nodes; ++i)
		printf("%u: %d\n", i, dist[i]);
	printf("\n");

	lg_free(lg);
}

static void
test_bipartite(void)
{
	unsigned int i, nodes, edges;
	int color[MAX_NODES] = {0};
	int x, y;
	list_graph_t *lg;

	printf("UNDIRECTED graph for the bipartite graph problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}
	
	if (check_bipartite(lg, color)) {
		printf("Nodes with colour 1:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 1)
				printf("%d ", i);
		printf("\nNodes with colour 2:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 2)
				printf("%d ", i);
		printf("\n");
	} else
		printf("The graph is not bipartite\n");

	lg_free(lg);
}

int
main(void)
{
	/* Ex 1 */
	//test_connected_comp();

	/* Ex 2 */
	test_topo_sort();

	/* Ex 3 */
	//test_min_dist();

	/* Ex 4 */
	test_bipartite();

	return 0;
}
