#include <tree.h>
#include <stck.h>

int search_DFS(tree_pp root, int val)
{
	if (!*root || !root) {
		printf("root node is NULL.\n");
		return FALSE;
	}

	tree_p tree1 = NULL;
	stack_p stack1 = NULL

	stack1 = get_stack();
	if ( !push(stack1, *root) {
		printf("push failed.\n");
		destroy_stack(stack1);
		return FALSE;
	}
	
	return TRUE;
}		 
