#include <stdio.h>
#include <stdlib.h>

#ifndef _TREE_H_

typedef struct tree tree;
typedef struct tree *tree_t;
typedef struct tree **tree_pp;

struct tree {
	int data;
	tree_t left;
	tree_t right;
};

/* Generate tree from an array of input values */
tree_t* generate_tree(int *arr, int len);

/* Destroy the tree */
int  delete_tree(tree_t root);

/* Print a tree */
int print_tree(tree_t root);

/* Traverse tree in BFS to find a given value */
int search_BFS(tree_t root, int val);

#endif
