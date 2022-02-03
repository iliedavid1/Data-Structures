#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ll_node_t ll_node_t;
struct ll_node_t
{
    void* data;
    ll_node_t* next;
};

typedef struct linked_list_t linked_list_t;
struct linked_list_t
{
    ll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};

linked_list_t*
ll_create(unsigned int data_size);

void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* data);

void
ll_free(linked_list_t** pp_list);

void
ll_print_int(linked_list_t* list);

int
ll_sum_nodes(linked_list_t A, linked_list_t B, int n);


int main()
{
	struct linked_list_t *A, *B, *C;

	A = ll_create(sizeof(int));
	B = ll_create(sizeof(int));
	C = ll_create(sizeof(int));

	int n_a;
	int n;

	for (int j = 0; j < 2; j++) {
		printf("Numar elemente lista %d:\n", j + 1);
		n_a = n;
		scanf("%d", &n);
		printf("Elemente lista %d:\n", j + 1);

		if (j == 0) {
			for (int i = 0; i < n; i++) {
				int elem;
				scanf("%d", &elem);
				ll_add_nth_node(A, i, &elem);
			}
		} else {
			for (int i = 0; i < n; i++) {
				int elem;
				scanf("%d", &elem);
				ll_add_nth_node(B, i, &elem);
			}
		}
	}

	if (n_a > n)
		n = n_a;


	for (int i = 0; i < n; i++) {
		int elem = ll_sum_nodes(*A, *B, i);
		printf("trece\n");
		ll_add_nth_node(C, i, &elem);
	}

	ll_print_int(A);
	ll_print_int(B);
	ll_print_int(C);

	ll_free(&A);
	ll_free(&B);
	ll_free(&C);
	

	return 0;
}


int
ll_sum_nodes(linked_list_t A, linked_list_t B, int n)
{
	struct ll_node_t *curr_A;
	struct ll_node_t *curr_B;

	curr_A = A.head;
	curr_B = B.head;

	int a_null = 0, b_null = 0;

	if (A.size <= n) {
		for (int i = 0; i < n; i++)
			curr_B = curr_B->next;
		return *(int*)curr_B->data;
	}

	if (B.size <= n) {
		for (int i = 0; i < n; i++)
			curr_A = curr_A->next;
		return *(int*)curr_A->data;
	}

	for (int i = 0; i < n; i++) {
		curr_A = curr_A->next;
		curr_B = curr_B->next;
	}

	int a = (*(int*)curr_A->data) + (*(int*)curr_B->data);
	return a;

}

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