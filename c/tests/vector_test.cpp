#include <vector>
#include <iostream>
#include <stdlib.h>
#include "bench.h"
#include "vector.h"

using std::vector;
using std::cout;
using std::endl;

typedef struct my_node{
	//int one,two,three;
	//int one;
	int one[10];
} my_node;

my_node dummy;

static inline void populateCPP(vector<my_node> &v){

	for(int i=0; i< 1000000; i++)
		v.push_back(dummy);
}

static inline void populateC(Vector* v){

	for(int i=0; i< 1000000; i++)
		vector_push_back(v,&dummy);
}

static void insertionTest(){

	CLOCK_BEGIN();

	for(int j=0; j<100; j++){
		vector<my_node> v;
		populateCPP(v);
	}

	CLOCK_STOP();

	cout << "Average C++ Vector Time: " << CLOCK_ELAPSED() / 100.0 << endl;

	CLOCK_BEGIN();

	for(int j=0; j<100; j++){

		Vector v = vector_alloc(sizeof(my_node));
		populateC(&v);
		vector_destroy(&v);
	}

	CLOCK_STOP();

	cout << "Average C   Vector Time: " << CLOCK_ELAPSED() / 100.0 << endl;
}

static void accessTest(){

	srand(time(0));

	vector<my_node> v;
	populateCPP(v);

	/* Time 1,000,000 random accesses */

	CLOCK_BEGIN();

	for(int j=0; j<1000000; j++){

		int idx = rand() % 1000000;
		my_node test = v[idx];
	}

	CLOCK_STOP();

	cout << "C++ Vector Time: " << CLOCK_ELAPSED() << endl;

	Vector v1 = vector_alloc(sizeof(my_node));
	populateC(&v1);

	CLOCK_BEGIN();

	my_node* arr = (my_node*) vector_get_array(&v1);

	for(int j=0; j<1000000; j++){

		int idx = rand() % 1000000;
		//my_node test = *((my_node*)vector_get_element(&v1,idx));
		my_node test = arr[idx];
	}

	CLOCK_STOP();

	cout << "C Vector Time: " << CLOCK_ELAPSED() << endl;

	vector_destroy(&v1);
}

int main(){

	insertionTest();
	//accessTest();

	return 0;
}
