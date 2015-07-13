#ifndef _LIBWOLF_DEBUG_H
#define _LIBWOLF_DEBUG_H

#include <ctime>
#include <iostream>
#include <cstdlib>

/* BENCHMARKING FUNCTIONS */

static clock_t tstart, tend;

static inline void CLOCK_BEGIN(){
	tstart = clock();
}

static inline void CLOCK_STOP(){
	tend = clock();
}

static inline double CLOCK_ELAPSED(){
	return (((double)(tend - tstart)) / CLOCKS_PER_SEC);
}


/* Misc debugging */

static inline void ASSERT(int expr){

	if(expr)
		return;

	std::cerr << "assert failed"<< std::endl;
	exit(EXIT_FAILURE);
}

static inline void ASSERT(int expr, const char* msg){

	if(expr)
		return;

	std::cerr << "assert failed: " << msg << std::endl;
	exit(EXIT_FAILURE);
}

#endif /* _LIBWOLF_BENCHMARK_H */
