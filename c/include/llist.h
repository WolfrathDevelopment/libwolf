#ifndef _LIBWOLF_LLIST_H
#define _LIBWOLF_LLIST_H

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Linked lists always come in handy...
 */

typedef struct _llnode {

	struct _llnode* next;
	struct _llnode* prev;

	void* data;

} llnode;

typedef struct _llist {

	llnode* head;
	llnode* tail;

	size_t objsize;
	int size;

} llist;


#define LLIST_SIZE(l)			(l.size)
#define LLIST_ENTRY(n,type)		((type*)n->data)

#define LLIST_FOR_EACH(l, itr)	\
	for(itr = l.head; itr != NULL; itr = itr->next)

#define LLIST_REVERSE_FOR_EACH(l, itr)	\
	itr = LLIST_SIZE(l) == 1 ? l.head : l.tail;	\
	for(; itr != NULL; itr = itr->prev)


inline void llist_init(llist* list, size_t sz){

	list->head = NULL;
	list->tail = NULL;
	list->objsize = sz;
	list->size = 0;
}

inline void llist_free(llist* lst){

	llnode* itr = lst->head;

	while(itr){

		llnode* next = itr->next;
		free(itr);
		itr = next;
	}
}

static inline llnode* get_llnode(llist* list, void* obj){

	llnode* nnode = (llnode*) malloc(list->objsize + sizeof(llnode));

	if(!nnode){
		fprintf(stderr, "malloc() failed for new llnode\n");
		exit(EXIT_FAILURE);
	}

	nnode->data = ((uint8_t*)nnode) + sizeof(llnode);
	memcpy(nnode->data, obj, list->objsize);

	nnode->next = NULL;
	nnode->prev = NULL;

	return nnode;
}

inline void llist_append(llist* list, void* obj){

	llnode* node = get_llnode(list, obj);

	if(!list->head){
		node->prev = NULL;
		node->next = list->tail;
		list->head = node;
	}
	else if(!list->tail){
		node->prev = list->head;
		node->next = NULL;
		list->tail = node;
		list->head->next = node;
	}
	else{
		list->tail->next = node;
		node->next = NULL;
		node->prev = list->tail;
		list->tail = node;
	}

	list->size++;
}

inline void llist_remove(llist* list, int idx){

	if(idx < 0 || idx > list->size - 1){
		fprintf(stderr, "Warning: invalid remove idx %i\n", idx);
		return;
	}

	/* We know list is not empty */

	if(list->size == 1){

		free(list->head);
		list->head= NULL;
	}
	else if(list->size == 2){

		if(idx){
			free(list->tail);
			list->tail = NULL;
			list->head->next = NULL;
		}
		else{
			free(list->head);
			list->head = list->tail;
			list->head->prev = NULL;
		}
	}
	else{
		
		llnode* itr = list->head;

		while(idx-- > 0)
			itr = itr->next;

		if(itr->prev)
			itr->prev->next = itr->next;

		if(itr->next)
			itr->next->prev = itr->prev;

		if(itr == list->head)
			list->head = itr->next;
		else if(itr == list->tail)
			list->tail = itr->prev;

		free(itr);
	}
	
	list->size--;
}


#ifdef __cplusplus
}
#endif

#endif /* _LIBWOLF_LLIST_H */
