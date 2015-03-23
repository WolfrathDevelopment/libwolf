#ifndef _LIBWOLF_BST_H
#define _LIBWOLF_BST_H

struct bst_node {

	struct bst_node* left;
	struct bst_node* right;
	struct bst_node* parent;

	int data;
};


/* Helper Functions */

#define BST_LEAF_NODE(x)	(!(x)->left && !(x)->right)
#define BST_LEFT_NODE(x)	((x) == (x)->parent->left)
#define BST_RIGHT_NODE(x)	((x) == (x)->parent->right)

struct bst_node* bst_alloc();

void
bst_insert(struct bst_node**, int);

struct bst_node*
bst_delete(struct bst_node**, int);

void
bst_print(struct bst_node*);

void 
bst_dealloc(struct bst_node*);

#endif /* _LIBWOLF_BST_H */
