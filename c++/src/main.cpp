#include "bst.h"
#include "types.h"
#include <iostream>

int main(){

	bst tree;

	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	tree.insert(4);
	tree.insert(8);
	tree.insert(2);
	tree.insert(6);

	tree.print();
	std::cout << "delete 5" << std::endl;
	tree.remove(5);

	tree.print();

	return 0;
}
