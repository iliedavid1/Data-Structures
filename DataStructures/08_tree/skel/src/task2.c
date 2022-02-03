/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - <resume_or_paste_the_task_here>
 */

#include "binary_tree.h"

#define MAX_NODES 100

unsigned int
is_complete(b_tree_t* b_tree)
{
	queue_t* q;
	b_node_t *b_node_tmp;
	q = q_create(sizeof(void**), MAX_NODES);

	if (b_tree->root == NULL)
		return 1;
	int ok = 0;

	q_enqueue(q, &b_tree->root);

	while (q_is_empty(q) == 0) {
		b_node_tmp = *(b_node_t**)q_front(q);
		q_dequeue(q);

		if (b_node_tmp->left != NULL) {
			if (ok == 1)
				return 0;
			q_enqueue(q, &b_node_tmp->left);
		} else {
			ok = 1;
		}

		if (b_node_tmp->right != NULL) {
			if (ok == 1)
				return 0;
			q_enqueue(q, &b_node_tmp->right);
		} else {
			ok = 1;
		}
	}

	return 1;
}

void print_data(void *data)
{
    printf("%d ", *(int *) data);
}

/*
void
create_tree(b_tree_t *b_tree) {
	int a = 1;
    b_tree->root = __b_node_create(&a, b_tree->data_size);
    a++;
    b_tree->root->left = __b_node_create(&a, b_tree->data_size);
    a++;
    b_tree->root->right = __b_node_create(&a, b_tree->data_size);
    a++;
    b_tree->root->left->left = __b_node_create(&a, b_tree->data_size);
    a++;
    b_tree->root->left->right = __b_node_create(&a, b_tree->data_size);
    a++;
    b_tree->root->right->right = __b_node_create(&a, b_tree->data_size);
}
*/

/*Pentru a testa programul trebuie adaugata functia __b_node_create in
 *binary_tree.h
 */
int main(void)
{
    /* TODO */
	b_tree_t *b_tree;
	
    b_tree = b_tree_create(sizeof(int));

    //create_tree(b_tree);
    if (is_complete(b_tree) == 1)
    	printf("Arbore complet\n");
    else
    	printf("Arbore incomplet\n");

    b_tree_print_preorder(b_tree, print_data);

    b_tree_free(b_tree, free);
    //exit(EXIT_FAILURE);
    return 0;
}
