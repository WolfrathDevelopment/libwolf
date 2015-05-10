#include "llist.h"
#include "stack.h"
#include <stdio.h>

int main(){

	stack s;

	/* Integer stack */

	stack_init(&s, sizeof(int));

	int i=4;

	stack_push(&s, &i);
	i++;
	stack_push(&s, &i);
	i++;
	stack_push(&s, &i);
	i++;
	stack_push(&s, &i);
	i++;

	stack_dump(&s);

	printf("\npeek: %i\n\n", *((int*)stack_peek(&s)));

	stack_pop(&s);
	stack_dump(&s);

	stack_pop(&s);
	stack_pop(&s);
	stack_dump(&s);

	stack_free(&s);

	return 0;
}
