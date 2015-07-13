#include "bst.h"
#include "types.h"
#include "debug.h"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

static bst_node* bstNodeAlloc(){

	bst_node* tmp = new bst_node;
	tmp->left = tmp->right = tmp->parent = NULL;
	tmp->data = 0;

	return tmp;
}

bst::bst(){
	pRoot = NULL;
}

bst_safe::bst_safe(){

	int rc;

	pRoot	= NULL;
	rc		= pthread_mutex_init(&pLock, NULL);

	ASSERT(!rc, "failed to init mutex in bst_safe instance");
}

static bst_node* recurse(bst_node* n, int val){

	if(!n)
		return NULL;

	if(n->data == val)
		return n;

	return n->data < val ? recurse(n->right,val) : recurse(n->left, val);
}

bst_node* bst::find(int val){
	return recurse(pRoot,val);
}

bool bst::insert(int data){

	bst_node** tree = &pRoot;	
	bst_node* n = bstNodeAlloc();

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

	bst_node** tree = &pRoot;

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

			if(tmp->isLeftNode())
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
		else if(del->isLeftNode())
			del->parent->left = del->left ? del->left : del->right;
		else
			del->parent->right = del->left ? del->left : del->right;
	}
	else{
		
		if(del == *tree)
			*tree = NULL;
		else if(del->isLeftNode())
			del->parent->left = NULL;
		else
			del->parent->right = NULL;
	}

	return del;
}

/***************************/

static void pad(char ch, int n){

	for (int  i = 0; i < n; i++)
		cout << ch;
}

static void drawTree(bst_node* n, int deep){

	if(!n) {

		pad('\t', deep);
		cout << "~" << endl;
		return;
	}

	drawTree(n->right, deep + 1);
	pad('\t', deep);
	cout << n->data << endl;
	drawTree(n->left, deep + 1);
}

bst_node* bst_safe::remove(int data){

	bst_node* ret;

	pthread_mutex_lock(&pLock);
	ret = bst::remove(data);
	pthread_mutex_unlock(&pLock);

	return ret;
}

bool bst_safe::insert(int data){

	bool ret;

	pthread_mutex_lock(&pLock);
	ret = bst::insert(data);
	pthread_mutex_unlock(&pLock);

	return ret;
}

/*************************/

void bst::print(){

	cout << "BST PRINT:" << endl;
	drawTree(pRoot, 0);
}


static void chainsaw(bst_node* n){
	
	if(!n)
		return;

	chainsaw(n->left);
	chainsaw(n->right);
	delete n;
}

bst::~bst(){
	chainsaw(pRoot);
}

bst_safe::~bst_safe(){
	pthread_mutex_destroy(&pLock);
}
