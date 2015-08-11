#include "tree.h"
#define ARR_LEN	5

int main()
{
	int count = 0;
	tree_pp head = NULL;
	int arr[ARR_LEN] = {10, 20, 30, 40, 50};

	printf("Calling generate_tree()\n");
	head = generate_tree(arr, ARR_LEN);

	count = print_tree(*head);
	printf("the number of nodes printed: %d\n", count);

	count = delete_tree(*head);
	printf("the number of nodes deleted: %d\n", count);
	
	return 0;
}

