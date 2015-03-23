#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

struct bst_node* bst_alloc(){

	struct bst_node* tmp = malloc(sizeof(struct bst_node));
	tmp->left = tmp->right = tmp->parent = NULL;
	tmp->data = 0;

	return tmp;
}

static struct bst_node*
find(struct bst_node* root, int val){

	if(!root)
		return NULL;

	if(root->data == val)
		return root;

	return root->data < val ? find(root->right,val) : find(root->left, val);
}

void                
bst_insert(struct bst_node** tree, int data){
	
	struct bst_node* n = bst_alloc();
	n->data = data;

	if(! *tree){
		*tree = n;
		return;
	}

	struct bst_node* p = *tree;
	struct bst_node* next = p;

	/* Place the child on the tree */

	while(next){

		p = next;
		
		if(data < next->data){

			if(!next->left){
	
				next->left = n;
				n->parent = next;
				break;
			}
			else
				next = next->left;
		}
		else{
			
			if(!next->right){

				next->right = n;
				n->parent = next;
				break;
			}
			else
				next = next->right;
		}
	}
}

struct bst_node*
bst_delete(struct bst_node** tree, int data){

	/* Must free node returned from this function! */

	struct bst_node* del = find(*tree, data);
	struct bst_node* tmp = del;
	struct bst_node* repl;

	/* Leaf node? 1 child? 2 children? */

	if(del->left && del->right){

		/* find smallest node in right subtree */

		tmp = tmp->right;

		while(tmp->left)
			tmp = tmp->left;

		del->data = tmp->data;

		if(tmp->right){
			repl = tmp->right;
			tmp->data = repl->data;
			tmp->right = NULL;
		}
		else{
			repl = tmp;

			if(BST_LEFT_NODE(tmp))
				tmp->parent->left = NULL;
			else
				tmp->parent->right = NULL;
		}

		del = repl;
		del->parent = NULL;
	}
	else if(del->left || del->right){

		if(del == *tree){
			*tree = del->left ? del->left : del->right;
			del->parent = NULL;
		}
		else if(BST_LEFT_NODE(del))
			del->parent->left = del->left ? del->left : del->right;
		else
			del->parent->right = del->left ? del->left : del->right;
	}
	else{
		
		if(del == *tree)
			*tree = NULL;
		else if(BST_LEFT_NODE(del))
			del->parent->left = NULL;
		else
			del->parent->right = NULL;
	}

	return del;
}

/***************************/

void padding ( char ch, int n )
{
	int i;
	for ( i = 0; i < n; i++ )
	putchar ( ch );
}

void structure ( struct bst_node *root, int level )
{

	if ( root == NULL ) {
		padding ( '\t', level );
		puts ( "~" );
	}
	else {
		structure ( root->right, level + 1 );
		padding ( '\t', level );
		printf ( "%d\n", root->data);
		structure ( root->left, level + 1 );
	}
}

/*************************/

void
bst_print(struct bst_node* tree){
	printf("BST PRINT:\n");
	structure(tree, 0);
}


static void chainsaw(struct bst_node* n){
	
	if(!n)
		return;

	chainsaw(n->left);
	chainsaw(n->right);
	free(n);
}

void bst_dealloc(struct bst_node* tree){
	
	chainsaw(tree);
}
