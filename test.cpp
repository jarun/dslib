#include "tree.h"
#define ARR_LEN	5

int main()
{
	tree_pp head = NULL;
	int arr[ARR_LEN] = {1, 2, 3, 4, 5};

	printf("Calling generate_tree()\n");
	head = (tree_pp)malloc(sizeof(tree_t));
	if(!head){
		printf("Error: could not allocate space.\n");
		return -1;
	}
	printf("head: %p\n", head);
	int count = generate_tree(head, arr, ARR_LEN);
	printf("the number of nodes created: %d\n", count);

	printf("head: %p\n", head);
	count = delete_tree(head);
	printf("the number of nodes deleted: %d\n", count);
	
	printf("head: %p\n", head);
	print_tree(head);
	return 0;
}

