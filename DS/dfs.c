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
		printf("root node is NULL.\n");
		return FALSE;
	}

	if (stop == TRUE)
		printf("TRUE\n");

	stack = get_stack();
	if (!push(stack, *root)) {
		printf("push failed.\n");
		destroy_stack(stack);
		return FALSE;
	}

	while ((node = pop(stack)) != NULL) {
		if (node->data == val) {
			log(INFO, "FOUND %d\n", val);
			ret = TRUE;
			break;
		}

		log(DEBUG, "tracking...\n");

		if (node->left) {
			if (!push(stack, node->left)) {
				printf(" push()failed.\n");
				ret = FALSE;
				break;
			}
		}

		if (node->right) {
			if (!push(stack, node->right)) {
				printf(" push()failed.\n");
				ret = FALSE;
				break;
			}
		}
	}

	destroy_stack(stack);
	return ret;
}
