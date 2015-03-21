#ifndef _LIBWOLF_VECTOR_H
#define _LIBWOLF_VECTOR_H

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Vectors are such useful c++ containers,
 * seems helpful to have an implementation for C
 */

typedef struct _vector {

	/* Pointer to begining of memory block */

	uint8_t* mem;

	int num_elements;
	int num_allocated;

	int lb_alloc_advise;
	int ub_alloc_advise;

	/* Size of a single element */

	size_t element_size;

} Vector;


/*
 * Allocate a vector to store elements of
 * size elem_sz
 *
 * Must be freed by vector_destroy()
 */

static inline Vector vector_alloc(size_t elem_sz){
	
	Vector v;
	v.element_size = elem_sz;

	v.lb_alloc_advise = 4096;
	v.ub_alloc_advise = 4096;

	v.mem = (uint8_t*) malloc(v.lb_alloc_advise * elem_sz);

	if(!v.mem){
		fprintf(stderr, "malloc() returned NULL in vector_alloc()\n");
		exit(EXIT_FAILURE);
	}

	v.num_allocated = v.lb_alloc_advise;
	v.num_elements = 0;

	return v;
}

static inline int vector_set_element(Vector* v, void* elem, int idx){

	if(idx < 0 || idx >= v->num_elements)
		return 0;

	memcpy(v->mem + (idx * v->element_size),elem,v->element_size);

	return 1;
}

static inline void vector_push_back(Vector* v, void* elem){

	int elements = v->num_elements;
	int allocated = v->num_allocated;
	size_t size = v->element_size;

	if(elements == allocated){

		/* GROW */

		size_t current = allocated * size;

		v->mem = (uint8_t*) realloc(v->mem, 
								current + (v->lb_alloc_advise * size));

		if(!v->mem){
			fprintf(stderr, "Vector resize failed: realloc() returned NULL\n");
			exit(EXIT_FAILURE);
		}

		v->num_allocated += v->lb_alloc_advise;
	}

	if(size == 4)
		*((uint32_t*)(v->mem + (size * elements))) = *((uint32_t*)elem);
	else
		memcpy(v->mem + (size * elements),elem,size);
	
	v->num_elements++;
}

static inline void* vector_get_element(Vector* v, int idx){

	if(idx < 0 || idx >= v->num_elements)
		return NULL;

	return ((void*)(v->mem + (idx * v->element_size)));
}

static inline void* vector_get_array(Vector* v){
	return ((void*)v->mem);
}

static inline int vector_size(Vector* v){
	return v->num_elements;
}

static inline void vector_destroy(Vector* v){
	free(v->mem);
}


#ifdef __cplusplus
}
#endif

#endif /* _LIBWOLF_VECTOR_H */
