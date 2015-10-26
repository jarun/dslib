#include "dlist.h"

#pragma once

/* Queue abstraction using a
   circular doubly linked list */
typedef struct {
	dlist_pp head;
} queue_t, *queue_p;

/* Create a new Queue */
queue_p get_queue();

/* Add a value to Queue */
bool enqueue(queue_p queue, void *val);

/* Remove a value from Queue */
void *dequeue(queue_p queue);

/* Clean up Queue */
bool destroy_queue(queue_p queue);
