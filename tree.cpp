#include "tree.h"

int generate_tree(tree_t *head, int* arr, int len)
{
	int i = 0;
	if(!head){
		printf("Error: Invalid head pointer.\n");
		return -1;
	}
	tree_t root = *head;
	if(!arr || !len){
		printf("Error: Invalid array.\n");
		return -1;
	}

	/*if(!root){
		root = (tree_t)malloc(sizeof(tree));
		if(!root){
			printf("Error: Could not malloc().\n");
			return -1;
		}
		root->data = arr[0];
		root->left = root->right = NULL;
	}*/

	for(i = 0; i < len; ++i){
		printf("i = %d\n", i);
		if(!root){
			root = (tree_t)malloc(sizeof(tree));
			root->data = arr[i];
			root->left = root->right = NULL;
		}
		else{
			while(root){
				if(arr[i] < root->data){
					if(!root->left){
						root->left = (tree_t)malloc(sizeof(tree));
						root = root->left;
						root->data = arr[i];
						root->left = root->right = NULL;
						break;
					}
					else{
						root = root->left;
						//continue;
					}
				}
				else if(arr[i] >= root->data){
					if(!root->right){
						root->right = (tree_t)malloc(sizeof(tree));
						root = root->right;
						root->data = arr[i];
						root->left = root->right = NULL;
						break;
					}
					else{
						root = root->right;
						//continue;
					}
				}
			}
		}
	}
	return i;
}

int delete_tree(tree_t *head)
{
	int count = 0;
	printf("In delete_tree().\n");
	if(!head){
		printf("Error: Invalid head pointer.\n");
		return -1;
	}
	if(!*head){
		printf("Error: root node does not exist.\n");
		return -1;
	}
	tree_t root = *head;
	if(root->left)
		count += delete_tree(&(root->left));
	if(root->right)
		count += delete_tree(&(root->right));
	printf("deleting a node.\n");
	free(root);
	++count;
	return count;
}

int print_tree(tree_t *head)
{
	printf("In print_tree().\n");
	if(!head){
		printf("Error: Invalid head pointer.\n");
		return -1;
	}
	if(!*head){
		printf("Error: root node does not exist.\n");
		return -1;
	}

	tree_t root = *head;
	printf("data: %d.\n", (root->data));
	
	if(root->left)
		print_tree(&(root->left));
	if(root->right)
		print_tree(&(root->right));

	return 0;
}
