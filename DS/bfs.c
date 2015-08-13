#include "tree.h"
#include "queue.h"

int search_BFS(tree_pp root, int val)
{
	tree_p node = NULL;
	queue_p queue = NULL;
	int ret = FALSE;

	if (!root || !*root) {
		log(ERROR, "tree or root is NULL!\n");
		return FALSE;
	}

	queue = get_queue();
	if (!enqueue(queue, *root)) {
		log(ERROR, "enqueue failed!\n");
		destroy_queue(queue);
		return FALSE;
	}

	while ((node = dequeue(queue)) != NULL) {
		if (node->data == val) {
			log(INFO, "FOUND");
			ret = TRUE;
			break;
		}

		log(DEBUG, "tracking...\n");

		if (node->left) {
			if (!enqueue(queue, node->left)) {
				log(ERROR, "enqueue failed!\n");
				ret = FALSE;
				break;
			}
		}

		if (node->right) {
			if (!enqueue(queue, node->right)) {
				log(ERROR, "enqueue failed!\n");
				ret = FALSE;
				break;
			}
		}
	}

	if (!ret)
		log(INFO, "NOT FOUND");

	destroy_queue(queue);
	return ret;
}
