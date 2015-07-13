#ifndef _LIBWOLF_BST_H
#define _LIBWOLF_BST_H

#include "types.h"

class bst;
class bst_safe;
class bst_node;

class bst_node {

public:

	bst_node* left;
	bst_node* right;
	bst_node* parent;

	int data;

	/* Helper Functions */

	inline bool isLeafNode();
	inline bool isLeftNode();
	inline bool isRightNode();
};

inline bool bst_node::isLeafNode(){
	return (!(this->left) && !(this->right));
}

inline bool bst_node::isLeftNode(){
	return (this == this->parent->left);
}

inline bool bst_node::isRightNode(){
	return (this == this->parent->right);
}

/* Binary Search Tree */

class bst {

	friend class bst_safe;

public:

	bst();
	~bst();

	bst_node* remove(int);
	bst_node* find(int);

	void print();
	bool insert(int);

private:

	bst_node*	pRoot;
};

/* Thread Safe Binary Search Tree */

class bst_safe : public bst {

public:

	bst_safe();
	~bst_safe();

	bst_node* remove(int);
	bool insert(int);

private:

	pthread_mutex_t		pLock;
};

#endif /* _LIBWOLF_BST_H */
