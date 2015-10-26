#include "tree.h"
#include "queue.h"

/*
 * Tree Breadth First Search implementation
 * Implements iterative search using a Queue
 * Checks for a match before adding a node to Queue
 *
 * PARAMS
 * ------
 * root: pointer to the root node pointer of a tree
 * val : value to search
 * stop: stop if val is found
 */

int search_BFS(tree_pp root, int val, bool stop)
{
	tree_p node = NULL;
	queue_p queue = NULL;
	int ret = FALSE;

	if (!root || !*root) {
		log(ERROR, "tree or root node is NULL!\n");
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
