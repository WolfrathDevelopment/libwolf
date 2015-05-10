#ifndef _LIBWOLF_STACK_H
#define _LIBWOLF_STACK_H

#include "types.h"
#include "llist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Stack implementation with linked lists
 */

typedef struct _stack {

	llist list;

} stack;

inline void stack_init(stack* s, size_t sz){
	llist_init(&s->list, sz);
}

inline size_t stack_size(stack* s){
	return LLIST_SIZE(s->list);
}

inline int stack_empty(stack* s){
	return stack_size(s) == 0;
}

inline void stack_free(stack* s){
	llist_free(&s->list);
}

inline void* stack_peek(stack* s){
	
	if(stack_empty(s))
		return NULL;

	if(LLIST_SIZE(s->list) == 1)
		return s->list.head->data;

	return s->list.tail->data;
}

inline void stack_push(stack* s, void* val){

	llist_append(&s->list, val);
}

inline void stack_pop(stack* s){

	if(stack_empty(s))
		return;

	llist_remove(&s->list, LLIST_SIZE(s->list) - 1);
}

inline void stack_dump(stack* s){

	llnode* itr;
	int i = 0;

	LLIST_REVERSE_FOR_EACH(s->list, itr)
		printf("depth %i: %i\n", i++, * LLIST_ENTRY(itr, int));

	printf("SIZE: %u\n", stack_size(s));
}

#ifdef __cplusplus
}
#endif

#endif /* _LIBWOLF_STACK_H */
