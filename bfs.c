#include "tree.h"
#include "queue.h"

int searh_BFS(tree_pp root, int val)
{
	tree_p node;
	int ret = FALSE;

	if (!root || !*root) {
		log(ERROR, "tree or root is NULL!\n");
		return FALSE;
	}

	queue_p queue = get_queue(queue);
	if (!enqueue(queue, *root)) {
		log(ERROR, "enqueue failed!\n");
		destroy_queue();
		return FALSE;
	}

	while ((node = dequeue(queue)) != NULL) {
		if (node->data == val) {
			log(INFO, "value found\n");
			ret = TRUE;
			break;
		}

		log("tracking...\n");

		if (node->left) {
			if (!enqueue(queue, node->left)) {
				destroy_queue();
				return FALSE;
			}
		}

		if (node->right) {
			if (!enqueue(queue, node->right)) {
				destroy_queue();
				return FALSE;
			}
		}
	}

	log(INFO, "value not found\n");
	destroy_queue(queue);
	return ret;
}
