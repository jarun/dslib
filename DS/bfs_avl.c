/*
 * Iterative BFS
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

#include "avl.h"
#include "queue.h"

/*
 * AVL Tree Breadth First Search implementation
 * Implements iterative search using a Queue
 * Checks for a match before adding a node to Queue
 *
 * PARAMS
 * ------
 * root: pointer to the root node pointer of an AVL tree
 * val : value to search
 * stop: stop if val is found
 */

int search_BFS_avl(avl_pp root, int val, bool stop)
{
	avl_p node = NULL;
	queue_p queue = NULL;
	int ret = FALSE;

	if (!root || !*root) {
		log(ERROR, "avl tree or root node is NULL!\n");
		return FALSE;
	}

	/* Check for a match in root node */
	node = *root;
	if (node->data == val) {
		log(INFO, "FOUND %d\n", val);

		if (stop)
			return TRUE;
	}

	queue = get_queue();

	/* Add root node to Queue */
	if (!enqueue(queue, *root)) {
		log(ERROR, "enqueue failed!\n");
		destroy_queue(queue);
		return FALSE;
	}

	/* Loop through all nodes in the Queue */
	while ((node = dequeue(queue)) != NULL) {
		log(INFO, "tracking...\n");

		/* Process left child of node */
		if (node->left) {
			if (node->left->data == val) {
				log(INFO, "FOUND %d\n", val);
				ret = TRUE;

				if (stop)
					break;
			}

			/* Add left child to Queue */
			if (!enqueue(queue, node->left)) {
				log(ERROR, "enqueue failed!\n");
				destroy_queue(queue);
				return FALSE;
			}
		}

		/* Process right child of node */
		if (node->right) {
			if (node->right->data == val) {
				log(INFO, "FOUND %d\n", val);
				ret = TRUE;

				if (stop)
					break;
			}

			/* Add right child to Queue */
			if (!enqueue(queue, node->right)) {
				log(ERROR, "enqueue failed!\n");
				destroy_queue(queue);
				return FALSE;
			}
		}
	}

	/* Report if no match was found */
	if (!ret)
		log(INFO, "NOT FOUND\n");

	destroy_queue(queue);

	return ret;
}
