#include "llist.h"
#include <stdio.h>

int main(){

	llist list;

	llist_init(&list, sizeof(int));

	llnode* itr;
	int i=0;
	
	llist_remove(&list, 0);

	llist_append(&list, &i);
	i++;
	llist_append(&list, &i);
	i++;
	llist_append(&list, &i);
	i++;
	llist_append(&list, &i);
	i=0;

	LLIST_FOR_EACH(list,itr)
		printf("Val at %i: %i\n", i++, * LLIST_ENTRY(itr, int));
	
	printf("llist size: %u\n", LLIST_SIZE(list));

	llist_remove(&list, 0);
	
	LLIST_FOR_EACH(list,itr)
		printf("Val at %i: %i\n", i++, *((int*)itr->data));
	
	printf("llist size: %u\n", LLIST_SIZE(list));

	llist_remove(&list, 2);
	
	LLIST_FOR_EACH(list,itr)
		printf("Val at %i: %i\n", i++, *((int*)itr->data));
	
	printf("llist size: %u\n", LLIST_SIZE(list));

	llist_remove(&list, 1);
	
	LLIST_FOR_EACH(list,itr)
		printf("Val at %i: %i\n", i++, *((int*)itr->data));
	
	printf("llist size: %u\n", LLIST_SIZE(list));

	llist_remove(&list, 1);

	llist_append(&list, &i);
	i++;
	llist_append(&list, &i);
	i++;
	llist_append(&list, &i);

	LLIST_FOR_EACH(list,itr)
		printf("Val at %i: %i\n", i++, *((int*)itr->data));
	
	printf("llist size: %u\n", LLIST_SIZE(list));

	llist_free(&list);

	return 0;
}
