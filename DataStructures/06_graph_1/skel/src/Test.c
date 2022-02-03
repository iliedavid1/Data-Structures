#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "LinkedList.h"

#define MAX_NODES 10
#define inf 1000000

void
print_matrix_graph(matrix_graph_t* mg)
{
	/* TODO */
	for (int i = 0; i < mg->nodes; i++) {
		for (int j = 0; j < mg->nodes; j++) {
			printf("%d ", mg->matrix[i][j]);
		}
		printf("\n");
	}
}

void
print_list_graph(list_graph_t* lg)
{
	/* TODO */
	for (int i = 0; i < lg->nodes; i++) {
		ll_node_t *curr = lg->neighbours[i]->head;
		printf("%d: ", i);
		while(curr) {
			printf("%d -> ", *(int*)curr->data);
			curr = curr->next;
		}
		printf("\n");
	}
}

void
dfs_list_graph(list_graph_t* lg,
		int node,
		int* visited,
		int* t_desc,
		int* t_tin)
{
	/* TODO */
	ll_node_t *curr;
	stack_t *st = st_create(sizeof(int));
	visited = malloc(lg->nodes * sizeof(int));
	t_desc = malloc(lg->nodes * sizeof(int));
	t_tin = malloc(lg->nodes * sizeof(int));

	for (int i = 0; i < lg->nodes; i++) {
		t_desc[i] = 0;
		t_tin[i] = 0;
		visited[i] = 0;
	}
	int time = 0;

	visited[node] = 1;
	t_desc[node] = time;
	st_push(st, &node);

	while(st_is_empty(st) != 1) {
		int v = *(int*)st_peek(st);
		curr = lg->neighbours[v]->head;
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
			time++;
			visited[*(int*)curr->data] = 1;
			t_desc[*(int*)curr->data] = time;
			printf("%d ", *(int*)curr->data);
			st_push(st, curr->data);
		} else {
			time++;
			t_tin[v] = time;
			st_pop(st);
		}
	}
	printf("\n");
	free(t_tin);
	free(t_desc);
	free(visited);
	st_free(st);
}

void
dfs_matrix_graph(matrix_graph_t* mg,
		 int node,
		 int* visited,
		 int* t_desc,
		 int* t_tin)
{
	/* TODO */
	stack_t *st = st_create(sizeof(int));
	visited = malloc(mg->nodes * sizeof(int));
	t_desc = malloc(mg->nodes * sizeof(int));
	t_tin = malloc(mg->nodes * sizeof(int));

	for (int i = 0; i < mg->nodes; i++) {
		t_desc[i] = 0;
		t_tin[i] = 0;
		visited[i] = 0;
	}
	int time = 0;

	visited[node] = 1;
	t_desc[node] = time;
	st_push(st, &node);

	while (st_is_empty(st) != 1) {
		int v = *(int*)st_peek(st);
		int i = 0;
		int ok = 0;
		while (i < mg->nodes) {
			if (visited[i] == 0 && mg->matrix[v][i] == 1) {
				ok = 1;
				break;
			}
			i++;
		}
		if (ok == 1) {
			time++;
			visited[i] = 1;
			t_desc[i] = time;
			printf("%d ", i);
			st_push(st, &i);
		} else {
			time++;
			t_tin[v] = time;
			st_pop(st);
		}
	}
	printf("\n");
	free(t_tin);
	free(t_desc);
	free(visited);
	st_free(st);
}

void
bfs_list_graph(list_graph_t* lg, int node, int* color, int* parent)
{
	/* TODO */
	int *d;
	int i;
	ll_node_t *curr;
	queue_t *q = q_create(sizeof(int), lg->nodes);
	d = (int *)malloc(lg->nodes * sizeof(int));
	color = malloc(lg->nodes * sizeof(int));
	parent = malloc(lg->nodes * sizeof(int));
	for (i = 0; i < lg->nodes; i++) {
		color[i] = 0;
		parent[i] = -1;
		d[i] = -1;
	}
	color[node] = 1;
	d[node] = 0;
	q_enqueue(q, &node);

	while (q_is_empty(q) != 1) {
		int v = *(int*)q_front(q);
		q_dequeue(q);
		printf("Vecinii lui %d: ", v);
		curr = lg->neighbours[v]->head;
		while (curr != NULL) {
			if (color[*(int*)curr->data] == 0) {
				color[*(int*)curr->data] = 1;
				parent[*(int*)curr->data] = v;
				d[*(int*)curr->data] = d[v] + 1;
				printf("%d cu departare de %d; ", *(int*)curr->data,
					d[*(int*)curr->data]);
				q_enqueue(q, curr->data);
			}
			curr = curr->next;
		}
		printf("\n");
		color[v] = 2;
	}
	q_free(q);
	free(d);
	free(color);
	free(parent);
}

void
bfs_matrix_graph(matrix_graph_t* mg, int node, int* color, int* parent)
{
	/* TODO */
	int *d;
	int i;
	queue_t *q = q_create(sizeof(int), mg->nodes);
	d = (int *)malloc(mg->nodes * sizeof(int));
	color = malloc(mg->nodes * sizeof(int));
	parent = malloc(mg->nodes * sizeof(int));
	for (i = 0; i < mg->nodes; i++) {
		color[i] = 0;
		parent[i] = -1;
		d[i] = -1;
	}
	color[node] = 1;
	d[node] = 0;
	q_enqueue(q, &node);

	while (q_is_empty(q) != 1) {
		int v = *(int*)q_front(q);
		q_dequeue(q);
		printf("ceva Vecinii lui %d: ", v);
		for (i = 0; i < mg->nodes; i++) {
			if (mg->matrix[v][i] == 0)
				continue;
			if (color[i] == 0) {
				color[i] = 1;
				parent[i] = v;
				d[i] = d[v] + 1;
				printf("%d cu departare de %d; ", i, d[i]);
				q_enqueue(q, &i);
			}
		}
		printf("\n");
		color[v] = 2;
	}
	q_free(q);
	free(d);
	free(color);
	free(parent);
}

void
floyd_warshall(matrix_graph_t* mg)
{
	/* TODO BONUS */
	int i, j, k;
	int **dist;
	dist = (int **)calloc(mg->nodes, sizeof(int*));
	for (i = 0; i < mg->nodes; i++) {
		dist[i] = (int *)calloc(mg->nodes, sizeof(int));
	}
	for (i = 0; i < mg->nodes; i++) {
		for (j = 0; j < mg->nodes; j++) {
			dist[i][j] = mg->matrix[i][j];
			if (mg->matrix[i][j] == 0 && i != j) {
				dist[i][j] = inf;
			}
		}
	}

	for (i = 0; i < mg->nodes; i++) {
		for (j = 0; j < mg->nodes; j++) {
			for (k = 0; k < mg->nodes; k++) {
				if (dist[j][i] + dist[i][k] < dist[j][k])
					dist[j][k] = dist[j][i] + dist[i][k];
			}
		}
	}

	for (i = 0; i < mg->nodes; i++) {
		for (j = 0; j < mg->nodes; j++) {
			if (dist[i][j] == inf) {
				printf("inf ");
			} else
				printf("%d ", dist[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < mg->nodes; i++) {
		free(dist[i]);
	}
	free(dist);
}

int
main()
{
	int nodes, edges;
	int x[MAX_NODES], y[MAX_NODES];
	int visited[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);

	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("-------------------------------- Test ListGraph "
		"--------------------------------\n");
	/* Test add_edge_list_graph has_edge_list_graph */

	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[2], numbers[4]));

	/* Test remove_edge_list_graph */
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[0], numbers[4]);

	linked_list_t* l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("Output asteptat: 1 2 3 4\n");

	printf("-------------------------------- Test MatrixGraph "
		"--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	lg_free(lg);
	mg_free(mg);

	lg = lg_create(8);
	int *color = NULL;
	int *parent = NULL;
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[1], numbers[2]);
	lg_add_edge(lg, numbers[3], numbers[4]);
	lg_add_edge(lg, numbers[5], numbers[4]);
	//lg_add_edge(lg, numbers[3], numbers[6]);
	//lg_add_edge(lg, numbers[3], numbers[7]);
	//lg_add_edge(lg, numbers[4], numbers[7]);
	//bfs_list_graph(lg, numbers[1], color, parent);
	dfs_list_graph(lg, numbers[0], visited, t_dest, t_fin);
	lg_free(lg);

	mg = mg_create(8);
	mg_add_edge(mg, numbers[1], numbers[2]);
	mg_add_edge(mg, numbers[1], numbers[3]);
	mg_add_edge(mg, numbers[1], numbers[4]);
	mg_add_edge(mg, numbers[2], numbers[5]);
	mg_add_edge(mg, numbers[3], numbers[6]);
	mg_add_edge(mg, numbers[3], numbers[7]);
	mg_add_edge(mg, numbers[4], numbers[7]);
	//print_matrix_graph(mg);
	//bfs_matrix_graph(mg, numbers[1], color, parent);
	//dfs_matrix_graph(mg, numbers[1], visited, t_dest, t_fin);
	//floyd_warshall(mg);
	mg_free(mg);
	return 0;
}
