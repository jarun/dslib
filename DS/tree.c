/*
 * Iterative Binary Search Tree implementation
 *
 * Author: Ananya Jana <ananya.jana@gmail.com>
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

#include "tree.h"

/*
 * Generate a tree from an array of integers
 */
tree_pp generate_tree(int *arr, int len)
{
	int i = 1;
	tree_pp head = NULL;
	tree_p root = NULL;

	if (!arr || !len) {
		log(ERROR, "Invalid array.\n");
		return NULL;
	}

	root = (tree_p) calloc(1, sizeof(tree_t));
	if (!root) {
		log(ERROR, "calloc failed.\n");
		return NULL;
	}
	root->data = arr[0];
	root->left = root->right = NULL;
	head = calloc(1, sizeof(tree_p));
	*head = root;

	for (; i < len; i++) {
		while (root) {
			if (arr[i] < root->data) {
				if (!root->left) {
					root->left = calloc(1, sizeof(tree_t));
					root = root->left;
					root->data = arr[i];
					root = *head; // Restart next element insertion from head
					break;
				}

				root = root->left;
			} else { // Insert equal or greater elements to right
				if (!root->right) {
					root->right = calloc(1, sizeof(tree_t));
					root = root->right;
					root->data = arr[i];
					root = *head; // Restart next element insertion from head
					break;
				}

				root = root->right;
			}
		}
	}

	return head;
}

/*
 * Delete all nodes of a tree
 */
int delete_tree(tree_p root)
{
	int count = 0;

	if (!root) {
		log(ERROR, "root invalid.\n");
		return -1;
	}

	if (root->left)
		count += delete_tree(root->left);

	if (root->right)
		count += delete_tree(root->right);

	free(root);
	root = NULL;

	return ++count;
}

/*
 * Destroy a tree
 */
int destroy_tree(tree_pp head)
{
	int count = 0;

	if (!head) {
		log(ERROR, "head invalid.\n");
		return -1;
	}

	count = delete_tree(*head);

	free(head);
	head = NULL;

	return count;
}

/*
 * Print the values in a tree in preorder
 */
int print_tree(tree_p root)
{
	int count = 0;

	if (!root) {
		log(ERROR, "root invalid.\n");
		return -1;
	}

	log(DEBUG, "data: %d.\n", root->data);
	++count;

	if (root->left)
		count += print_tree(root->left);
	if (root->right)
		count += print_tree(root->right);

	return count;
}
