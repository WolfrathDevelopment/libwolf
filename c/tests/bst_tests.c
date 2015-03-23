#include "bst.h"
#include "types.h"
#include <stdio.h>

int main(){

	struct bst_node* tree = NULL;

	bst_insert(&tree, 5);
	bst_insert(&tree, 3);
	bst_insert(&tree, 7);
	bst_insert(&tree, 4);
	bst_insert(&tree, 8);
	bst_insert(&tree, 2);
	bst_insert(&tree, 6);

	bst_print(tree);
	printf("delete %i\n",5);
	bst_delete(&tree, 5);

	bst_print(tree);

	return 0;
}
