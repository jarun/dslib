#include "tree.h"

tree_p* generate_tree(int* arr, int len)
{
	int i = 0;
	tree_p *head;
	if(!arr || !len){
		printf("Error: Invalid array.\n");
		return NULL;
	}
	
	tree_p root = NULL;
	if(!root){
		root = (tree_p)malloc(sizeof(tree));
		if(!root){
			printf("Error: Could not malloc().\n");
			return NULL;
		}
		root->data = arr[0];
		root->left = root->right = NULL;
		head = (tree_p*)malloc(sizeof(tree_p));
		*head = root;
	}

	for(i = 1; i < len; ++i){
		if(!root){
			root = (tree_p)malloc(sizeof(tree));
			root->data = arr[i];
			root->left = root->right = NULL;
		}
		else{
			while(root){
				if(arr[i] < root->data){
					if(!root->left){
						root->left = (tree_p)malloc(sizeof(tree));
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
						root->right = (tree_p)malloc(sizeof(tree));
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
	return head;
}

int delete_tree(tree_p root)
{
	int count = 0;
	//printf("In delete_tree().\n");
	if(!root){
		printf("Error: Invalid root pointer.\n");
		return -1;
	}
	if(root->left)
		count += delete_tree(root->left);
	if(root->right)
		count += delete_tree(root->right);
	//printf("deleting a node.\n");
	free(root);
	++count;
	return count;
}

int print_tree(tree_p root)
{
	int count = 0;
	//printf("In print_tree().\n");
	if(!root){
		printf("Error: Invalid root pointer.\n");
		return -1;
	}

	printf("data: %d.\n", root->data);
	++count; 
	
	if(root->left)
		count += print_tree(root->left);
	if(root->right)
		count += print_tree(root->right);

	return count;
}
