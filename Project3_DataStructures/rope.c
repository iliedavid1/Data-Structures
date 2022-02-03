/*Copyright Ilie David, Cosor Miahi 2021 */
#include "./rope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define EMPTY ""

char *strdup(const char *s);

RopeNode* makeRopeNode(const char* str) {
    RopeNode *node = malloc(sizeof(*node));

    node->left = node->right = NULL;
    node->str = str;
    node->weight = strlen(str);

    return node;
}

RopeTree* makeRopeTree(RopeNode* root) {
    RopeTree *tree = malloc(sizeof(*tree));

    tree->root = root;

    return tree;
}

void printRopeNode(RopeNode* rn) {
    if (!rn)
        return;

    if (!(rn->left) && !(rn->right)) {
        printf("%s", rn->str);
        return;
    }

    printRopeNode(rn->left);
    printRopeNode(rn->right);
}

void printRopeTree(RopeTree* rt) {
    if (rt && rt->root) {
        printRopeNode(rt->root);
        printf("%s", "\n");
    }
}

void debugRopeNode(RopeNode* rn, int indent) {
    if (!rn)
        return;

    for (int i = 0; i < indent; ++i)
        printf("%s", " ");

    if (!strcmp(rn->str, EMPTY))
        printf("# %d\n", rn->weight);
    else
        printf("%s %d\n", rn->str, rn->weight);

    debugRopeNode(rn->left, indent+2);
    debugRopeNode(rn->right, indent+2);
}

int getTotalWeight(RopeNode* rt) {
    if (!rt)
        return 0;

    return rt->weight + getTotalWeight(rt->right);
}

/* Concateneaza cei 2 arbori */
RopeTree* concat(RopeTree* rt1, RopeTree* rt2) {
    RopeTree *tree = makeRopeTree(makeRopeNode(strdup(EMPTY)));

    tree->root->left = rt1->root;
    tree->root->right = rt2->root;

    tree->root->weight = getTotalWeight(tree->root->left);

    return tree;
}

/* Se parcurge arborele in functie de idx si se returneaza
 * char-ul de pe pozitia idx
 */
char indexRope(RopeTree* rt, int idx) {
    RopeNode *curr = rt->root;

    while (1) {
        if (curr->weight > idx) {
            if (curr->left != NULL) {
                curr = curr->left;
                continue;
            }
            return curr->str[idx];
        } else {
            if (curr->right != NULL) {
                idx = idx - curr->weight;
                curr = curr->right;
                continue;
            }
            return curr->str[idx];
        }
    }
}

/* Se apeleaza functia indexRope de (end - start + 1)
 * ori si se stocheaza intr-un string rezultatul
 */
char* search(RopeTree* rt, int start, int end) {
    char *str = malloc(sizeof(*str) * (end - start + 1));

    int i = 0, k = 0;
    for (i = start; i < end; i++) {
        str[k] = indexRope(rt, i);
        k++;
    }
    str[k] = '\0';

    return str;
}

/* Se cloneaza un arbore */
static RopeNode* clone_rope_tree(RopeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    RopeNode *new = malloc(sizeof(*new));

    new->weight = root->weight;
    new->str = strdup(root->str);

    new->left = clone_rope_tree(root->left);
    new->right = clone_rope_tree(root->right);

    return new;
}

/* Se rebalanseaza greutatile nodurilor din rebalance */
static void rebalance_weight(RopeNode **rebalance, int size) {
    int i = 0;

    for (i = size - 1; i >= 0; i--) {
        rebalance[i]->weight = getTotalWeight(rebalance[i]->left);
    }
}

/* Se imparte un arbore in 2 arbori */
SplitPair split(RopeTree* rt, int idx) {
    RopeNode *clone_root = clone_rope_tree(rt->root);
    RopeNode *curr = clone_root;
    SplitPair sp;

    int ok = 0, copy = idx;

    /* In cele 2 if-uri se verifica cazurile speciale */
    if (idx == 0) {
        sp.left = makeRopeNode(strdup(EMPTY));
        sp.right = curr;
        return sp;
    }

    if (idx >= getTotalWeight(curr)) {
        sp.left = curr;
        sp.right = makeRopeNode(strdup(EMPTY));
        return sp;
    }

    /* Se verifica daca trebuie impartita o frunza in 2 */
    while (1) {
        if (curr->weight > idx) {
            if (curr->left != NULL) {
                curr = curr->left;
                continue;
            }
            ok = 1;
            break;
        } else {
            if (curr->right != NULL) {
                idx = idx - curr->weight;
                curr = curr->right;
                continue;
            }
            if (idx < curr->weight) {
                ok = 1;
                break;
            }
            break;
        }
    }

    /* Cazul in care o frunza trebuie sparta in 2 frunze */
    if (ok == 1) {
        char *str_left = malloc(sizeof(*str_left) * (idx + 1));
        char *str_right = malloc(sizeof(*str_right) * (curr->weight - idx + 1));

        int i = 0, k = 0;

        for (i = 0; i < idx; i++) {
            str_left[i] = curr->str[i];
        }
        str_left[idx] = '\0';

        for (i = idx; i < curr->weight; i++) {
            str_right[k] = curr->str[i];
            k++;
        }
        str_right[k] = '\0';

        RopeNode *left = makeRopeNode(strdup(str_left));
        RopeNode *right = makeRopeNode(strdup(str_right));

        free(str_left);
        free(str_right);

        curr->left = left;
        curr->right = right;

        free((void *)curr->str);
        curr->str = strdup(EMPTY);

        curr->weight = idx;
    }

    curr = clone_root;
    RopeNode *right_node;
    RopeNode *rebalance[100];

    int ok1 = 0, size = 0;

    /* Spargerea arborelui in 2 arbori */
    while (1) {
        if (curr->weight >= copy) {
            if (curr->left != NULL) {
                if (ok1 == 0) {
                    ok1 = 1;
                    right_node = curr->right;
                } else {
                    RopeNode *new_right = makeRopeNode(strdup(EMPTY));

                    new_right->left = curr->right;
                    new_right->right = right_node;
                    new_right->weight = getTotalWeight(new_right->left);

                    right_node = new_right;
                }

                curr->right = NULL;
                rebalance[size] = curr;
                size++;
                curr = curr->left;
                continue;
            }
            break;
        } else {
            if (curr->right != NULL) {
                copy = copy - curr->weight;
                curr = curr->right;
                continue;
            }
            break;
        }
    }

    /* rebalansarea greutatilor arborelui stang */
    rebalance_weight(rebalance, size);

    sp.left = clone_root;
    sp.right = right_node;

    return sp;
}

/* Insertul presupune un split si 2 concat-uri */
RopeTree* insert(RopeTree* rt, int idx, const char* str) {
    SplitPair pair = split(rt, idx);

    RopeNode *parent = makeRopeNode(strdup(EMPTY));

    parent->left = pair.left;
    parent->right = makeRopeNode(str);

    parent->weight = getTotalWeight(parent->left);

    RopeNode* big_parent = makeRopeNode(strdup(EMPTY));

    big_parent->left = parent;
    big_parent->right = pair.right;

    big_parent->weight = getTotalWeight(big_parent->left);

    return makeRopeTree(big_parent);
}

/* functie de free pentru delete */
static void freeRopeNode(RopeNode* rn) {
    if (rn == NULL)
        return;

    free((void*)rn->str);
    freeRopeNode(rn->left);
    freeRopeNode(rn->right);
    free(rn);
}

/* Delete-ul presupune 2 split-uri si un concat */
RopeTree* delete(RopeTree* rt, int start, int len) {
    SplitPair pair_left = split(rt, start);

    RopeTree *tree = makeRopeTree(pair_left.right);

    SplitPair pair_right = split(tree, len);

    RopeNode *parent = makeRopeNode(strdup(EMPTY));

    parent->left = pair_left.left;
    parent->right = pair_right.right;

    parent->weight = getTotalWeight(parent->left);

    freeRopeNode(pair_left.right);
    freeRopeNode(pair_right.left);
    free(tree);

    return makeRopeTree(parent);
}
