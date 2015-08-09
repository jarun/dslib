#include <dlist.h>

typedef struct {
	dlist_p *head;
} queue_t, *queue_p;

queue_p get_queue();
bool enqueue(queue_p queue, void *val);
void * dequeue(queue_p queue);
bool destroy_queue(queue_p queue);
