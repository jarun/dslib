/*
 * AVL Tree abstraction
 * Ref: https://en.wikipedia.org/wiki/AVL_tree
 *
 * Author: Arun Prakash Jana <engineerarun@gmail.com>
 * Copyright (C) 2015 by Arun Prakash Jana <engineerarun@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dslib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "common.h"

#pragma once

typedef struct avl {
	int keyNode;
	int data;
	struct avl *left;
	struct avl *right;
	int height;
} avl_t, *avl_p, **avl_pp;

/* Generate AVL tree from an array of input values */
avl_pp generate_avl(int *arr, int len);

/* Initialize an AVL tree */
avl_pp init_avl(void);

/* Insert a node in AVL tree */
bool insert_avl_node(avl_pp head, int key, int data);


/* Delete a node from AVL tree */
bool delete_avl_node(avl_pp head, int key);

/* Destroy the tree */
int destroy_avl(avl_pp head);
// avl will be destroy isn't necessary sincronize it (is better not destroy)

/* Print a tree in preorder */
int print_avl(avl_p root, avl_p parent);

/* Traverse tree in BFS to find a given value */
int search_BFS_avl(avl_pp root, int key, bool stop);

/*=======================================================*/
/*         Library ThreadSafe APIs start here            */
/*=======================================================*/

//The struct is a generalization of avl_pp, to include for every tree one semaphore
typedef struct avlThSafe {
	avl_pp avlRoot;
	int semId;
} avl_pp_S;

/* Generate AVL tree from an array of input values */
avl_pp_S generate_avl_S(int *arr, int len);

/* Initialize an AVL tree */
avl_pp_S init_avl_S(void);

/* Insert a node in AVL tree */
bool insert_avl_node_S(avl_pp_S head, int key, int data);

/* Delete a node from AVL tree */
bool delete_avl_node_S(avl_pp_S head, int key);

/* Destroy the tree */
/** [][] avl will be destroy isn't necessary sincronize it (is better not destroy) **/

/* Print a tree in preorder, start by root */
int print_avl_S(avl_pp_S root);

/* Traverse tree in BFS to find a given value */
int search_BFS_avl_S(avl_pp_S root, int key, bool stop);