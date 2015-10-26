#include "dlist.h"

#pragma once

/* Stack abstraction using a
   circular doubly linked list */
typedef struct {
	dlist_pp head;
} stack_t, *stack_p;

/* Create a new Stack */
stack_p get_stack();

/* Push a value to Stack */
bool push(stack_p stack, void *val);

/* Pop a value from Stack */
void *pop(stack_p stack);

/* Clean up Stack */
bool destroy_stack(stack_p stack);
