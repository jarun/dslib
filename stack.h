#include "dlist.h"

#pragma once

typedef struct {
	dlist_pp head;
} stack_t, *stack_p;

stack_p get_stack();
bool push(stack_p stack, void *val);
void * pop(stack_p stack);
bool destroy_stack(stack_p stack);
