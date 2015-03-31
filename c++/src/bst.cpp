#include "bst.h"
#include "types.h"
#include <cstdlib>
#include <iostream>

bst_node* bst::nodeAlloc(){

	bst_node* tmp = new bst_node;
	tmp->left = tmp->right = tmp->parent = NULL;
	tmp->data = 0;

	return tmp;
}

bst::bst(){
	root = NULL;
}

static bst_node* recurse(bst_node* n, int val){

	if(!n)
		return NULL;

	if(n->data == val)
		return n;

	return n->data < val ? recurse(n->right,val) : recurse(n->left, val);
}

bst_node* bst::find(int val){
	return recurse(root,val);
}

bool bst::insert(int data){

	bst_node** tree = &root;	
	bst_node* n = nodeAlloc();

	if(!n)
		return false;

	n->data = data;

	if(!*tree){
		*tree = n;
		return true;
	}

	bst_node* p = *tree;
	bst_node* next = p;

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

	return true;
}

bst_node* bst::remove(int data){

	bst_node** tree = &root;

	/* Must free node returned from this function! */

	bst_node* del = recurse(*tree, data);

	if(!del)
		return NULL;

	bst_node* tmp = del;
	bst_node* repl;

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

static void pad(char ch, int n){

	for (int  i = 0; i < n; i++)
		std::cout << ch;
}

static void drawTree(bst_node* n, int deep){

	if(!n) {

		pad('\t', deep);
		std::cout << "~" << std::endl;
		return;
	}

	drawTree(n->right, deep + 1);
	pad('\t', deep);
	std::cout << n->data << std::endl;
	drawTree(n->left, deep + 1);
}

/*************************/

void bst::print(){

	std::cout << "BST PRINT:" << std::endl;
	drawTree(root, 0);
}


static void chainsaw(bst_node* n){
	
	if(!n)
		return;

	chainsaw(n->left);
	chainsaw(n->right);
	delete n;
}

bst::~bst(){
	chainsaw(root);
}
