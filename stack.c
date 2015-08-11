#include "stack.h"

bool destroy_stack(stack_p stack);

stack_p get_stack()
{
	stack_p stack = calloc(1, sizeof(stack_t));
	stack->head = calloc(1, sizeof(dlist_p *));
	return stack;
}

bool push(stack_p stack, void *val)
{
	dlist_p nodeptr = calloc(1, sizeof(dlist_t));
	nodeptr->data = val;
	if (add_head_dlist(stack->head, nodeptr))
		return TRUE;
	else
		return FALSE;
}

void * pop(stack_p stack)
{
	void *data = get_head_dlist(stack->head);

	if (delete_head_dlist(stack->head) == -1)
		log(DEBUG, "head or first node is NULL!\n");

	return data;
}

bool destroy_stack(stack_p stack)
{
	if (destroy_dlist(stack->head) == -1)
		return FALSE;

	free(stack->head);
	free(stack);

	return TRUE;
}
