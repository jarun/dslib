#include <stdio.h>
#include <stdlib.h>

#pragma once

typedef struct tree tree;
typedef struct tree *tree_t;
typedef struct tree **tree_pp;

struct tree {
	int data;
	tree_t left;
	tree_t right;
};

/* Generate tree from an array of input values */
int generate_tree(tree_t *root, int *arr, int len);

/* Destroy the tree */
int  delete_tree(tree_t *root);

/* Print a tree */
int print_tree(tree_t *root);

/* Traverse tree in BFS to find a given value */
int searh_BFS(tree_t *root, int val);
