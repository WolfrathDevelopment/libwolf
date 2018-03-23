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

	uint64_t rc = pthread_mutex_init(&pLock, NULL);
	WL_ASSERT(!rc, "failed to init mutex in bst instance");
}

/*
 * TODO find() holds the lock while recursing
 * Perhaps we can make this better
 */
static bst_node* recurse(bst_node* n, int val){

	if(!n)
		return NULL;

	if(n->data == val)
		return n;

	return n->data < val ? recurse(n->right,val) : recurse(n->left, val);
}

bst_node* bst::find(int val){

	bst_node* foundNode = NULL;

	pthread_mutex_lock(&pLock);
	foundNode = recurse(pRoot, val);
	pthread_mutex_unlock(&pLock);

	return foundNode;
}

bool bst::insert(int data){

	bst_node* n = bstNodeAlloc();
	if(!n) return false;

	pthread_mutex_lock(&pLock);

	bst_node** tree = &pRoot;	
	n->data = data;

	if( ! *tree) {
		*tree = n;
	}
	else {

		bst_node* p = *tree;
		bst_node* next = p;

		/* Place the child on the tree */
	
		while(next) {

			p = next;
			
			if(data < next->data) {

				if(!next->left) {
	
					next->left = n;
					n->parent = next;
					break;
				}
				else {
					next = next->left;
				}
			}
			else {
			
				if(!next->right) {

					next->right = n;
					n->parent = next;
					break;
				}
				else {
					next = next->right;
				}
			}
		}
	}

	pthread_mutex_unlock(&pLock);
	return true;
}

bst_node* bst::remove(int data){

	pthread_mutex_lock(&pLock);

	/* Must free node returned from this function! */

	bst_node** tree = &pRoot;
	bst_node* del = recurse(*tree, data);

	if(del) {

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
	}

	pthread_mutex_unlock(&pLock);
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

/*************************/

void bst::print(){

	cout << "BST PRINT:" << endl;
	drawTree(pRoot, 0);
}

/*
 * Helper function to delete all the nodes in a tree
 * Assumes the lock is already held
 */
static void chainsawTreeWithLock(bst_node* n) {
	
	if(!n)
		return;

	chainsawTreeWithLock(n->left);
	chainsawTreeWithLock(n->right);
	delete n;
}

bst::~bst() {

	pthread_mutex_lock(&pLock);
	chainsawTreeWithLock(pRoot);
	pthread_mutex_unlock(&pLock);
	pthread_mutex_destroy(&pLock);
}

