/*
 * Iterative DFS
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

#include "tree.h"
#include "stack.h"

/*
 * Tree Depth First Search implementation
 * Implements iterative search using a Stack
 * Checks for a match before adding a node to Stack
 *
 * PARAMS
 * ------
 * root: pointer to the root node pointer of a tree
 * val : value to search
 * stop: stop if val is found
 */

int search_DFS(tree_pp root, int val, bool stop)
{
	int ret = FALSE;
	tree_p node = NULL;
	stack_p stack = NULL;

	if (!root || !*root) {
		log(ERROR, "tree or root node is NULL.\n");
		return FALSE;
	}

	/* Check for a match in root node */
	node = *root;
	if (node->data == val) {
		log(INFO, "FOUND %d\n", val);

		if (stop)
			return TRUE;
	}

	stack = get_stack();

	/* Add root node to Stack */
	if (!push(stack, *root)) {
		log(ERROR, "push failed!\n");
		destroy_stack(stack);
		return FALSE;
	}

	/* Process all valid nodes */
	while (node) {
		log(INFO, "tracking...\n");

		/* Match and add complete
		   left subtree to Stack */
		while (node->left) {
			if (node->left->data == val) {
				log(INFO, "FOUND %d\n", val);
				ret = TRUE;

				if (stop) {
					node = NULL;
					break;
				}
			}

			/* Add node to stack */
			if (!push(stack, node->left)) {
				log(ERROR, "push failed!\n");
				destroy_stack(stack);
				return FALSE;
			}

			node = node->left;
		}

		while ((node = pop(stack)) != NULL) {
			/* Process right child of node */
			if (node->right) {
				if (node->right->data == val) {
					log(INFO, "FOUND %d\n", val);
					ret = TRUE;

					if (stop) {
						node = NULL;
						break;
					}
				}

				/* Add right child to Stack */
				if (!push(stack, node->right)) {
					log(ERROR, "push failed!\n");
					destroy_stack(stack);
					return FALSE;
				}

				node = node->right;
				/* Break inner loop if there's a right node */
				break;
			}
		}
	}

	/* Report if no match was found */
	if (!ret)
		log(INFO, "NOT FOUND\n");

	destroy_stack(stack);

	return ret;
}
