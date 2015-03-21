#include "types.h"
#include "slab.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){

	slab_init(40);

	void* obj0;

	int i;
	for(i=0; i<500000; i++){

		obj0 = slab_alloc();
		slab_free(obj0);
	}

	slab_destroy();

	return 0;
}
