#ifndef _LIBWOLF_BST_H
#define _LIBWOLF_BST_H

typedef struct _bst_node {

	struct _bst_node* left;
	struct _bst_node* right;
	struct _bst_node* parent;

	int data;

} bst_node;


/* Helper Functions */

static inline bool BST_LEAF_NODE(bst_node* n){
	return (!(n->left) && !(n->right));
}

static inline bool BST_LEFT_NODE(bst_node* n){
	return (n == n->parent->left);
}

static inline bool BST_RIGHT_NODE(bst_node* n){
	return (n == n->parent->right);
}


class bst {

public:

	bst();
	~bst();

	bool insert(int);

	bst_node* remove(int);
	bst_node* find(int);

	void print();

private:

	bst_node*	root;
	bst_node*	nodeAlloc();

};

#endif /* _LIBWOLF_BST_H */
