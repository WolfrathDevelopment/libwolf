#ifndef _LIBWOLF_BST_H
#define _LIBWOLF_BST_H

#include "types.h"

// Forward declaration 
class bst;
class bst_node;

//template <typename BST_T>
class bst_node {

public:

	bst_node* left;
	bst_node* right;
	bst_node* parent;

	//BST_T data;
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
	bool retVal = false;
	if(this->parent) {
		retVal = (this == this->parent->left);
	}
	return retVal;
}

inline bool bst_node::isRightNode(){
	bool retVal = false;
	if(this->parent) {
		retVal = (this == this->parent->right);
	}
	return retVal;
}

/* Binary Search Tree */

class bst {

public:

	bst();
	~bst();

	bst_node* remove(int);
	bst_node* find(int);

	void print();
	bool insert(int);

protected:

	bst_node*		pRoot;
	pthread_mutex_t		pLock;
};


#endif /* _LIBWOLF_BST_H */
