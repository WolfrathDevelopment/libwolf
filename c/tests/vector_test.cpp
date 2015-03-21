#include <vector>
#include <iostream>
#include "include/bench.h"
#include "include/vector.h"

using std::vector;
using std::cout;
using std::endl;

struct my_node{
	int one,two,three;
};

int main(){

	struct my_node n;

	n.one = 1;
	n.two = 2;
	n.three = 3;

	BEGIN_CLOCK();

	for(int j=0; j<100; j++){

		vector<struct my_node> v;

		for(int i=0; i< 1000000; i++)
			v.push_back(n);
	}

	STOP_CLOCK();

	cout << "Average c++ Vector Time: " << CLOCK_ELAPSED() / 10.0 << endl;

	BEGIN_CLOCK();

	for(int j=0; j<100; j++){

		Vector v = vector_alloc(sizeof(struct my_node));

		for(int i=0; i< 1000000; i++)
			vector_push_back(&v,&n);

		vector_destroy(&v);
	}

	STOP_CLOCK();

	cout << "Average c   Vector Time: " << CLOCK_ELAPSED() / 10.0 << endl;

	return 0;
}
