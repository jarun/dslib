#include "queue.h"

queue_p get_queue()
{
	queue_p queue = calloc(1, sizeof(queue_t));
	queue->head = calloc(1, sizeof(dlist_p *));
	return queue;
}

bool enqueue(queue_p queue, void *val)
{
	dlist_p nodeptr = calloc(1, sizeof(dlist_t));
	nodeptr->data = val;
	if (add_head_dlist(queue->head, nodeptr))
		return TRUE;
	else
		return FALSE;
}

void * dequeue(queue_p queue)
{
	void *data = get_tail_dlist(queue->head);

	if (delete_tail_dlist(queue->head) == -1)
		printf("head or first node is NULL!\n");

	return data;
}

bool destroy_queue(queue_p queue)
{
	if (destroy_dlist(queue->head) == -1)
		return FALSE;

	free(queue->head);
	free(queue);

	return TRUE;
}
