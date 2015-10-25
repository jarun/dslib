#include "tree.h"
#include "stack.h"

/*
 * Tree Depth First Search implementation
 * Implements iterative search using a Stack
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

	node = *root;
	if (node->data == val) {
		log(INFO, "FOUND %d\n", val);

		if (stop)
			return TRUE;
	}

	stack = get_stack();
	if (!push(stack, *root)) {
		log(ERROR, "push failed!\n");
		destroy_stack(stack);
		return FALSE;
	}

	while (node) {
		log(INFO, "tracking...\n");

		while (node->left) {
			if (node->left->data == val) {
				log(INFO, "FOUND %d\n", val);
				ret = TRUE;

				if (stop) {
					node = NULL;
					break;
				}
			}

			if (!push(stack, node->left)) {
				log(ERROR, "push failed!\n");
				ret = FALSE;
				break;
			}

			node = node->left;
		}

		while ((node = pop(stack)) != NULL) {
			if (node->right) {
				if (node->right->data == val) {
					log(INFO, "FOUND %d\n", val);
					ret = TRUE;

					if (stop) {
						node = NULL;
						break;
					}
				}

				if (!push(stack, node->right)) {
					log(ERROR, "push failed!\n");
					ret = FALSE;

					/* Break out of both the loops */
					node = NULL;
				} else
					node = node->right;

				/* Always break inner loop
				   if there's a right node */
				break;
			}
		}
	}

	if (!ret)
		log(INFO, "NOT FOUND\n");

	destroy_stack(stack);

	return ret;
}
