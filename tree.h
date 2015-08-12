#include "common.h"

#pragma once

typedef struct tree tree;
typedef struct tree *tree_p;
typedef struct tree **tree_pp;

struct tree {
	int data;
	tree_p left;
	tree_p right;
};

/* Generate tree from an array of input values */
tree_p* generate_tree(int *arr, int len);

/* Destroy the tree */
int  delete_tree(tree_p root);

/* Print a tree */
int print_tree(tree_p root);

/* Traverse tree in BFS to find a given value */
int search_BFS(tree_pp root, int val);
