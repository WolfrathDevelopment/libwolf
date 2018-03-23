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

#define WL_ASSERT(expr,msg) \
	_ASSERT(expr, msg, __FILE__, __LINE__)

static inline void _ASSERT(int expr, const char* msg, const char* file, uint64_t lineNumber) {

	if(expr)
		return;

	std::cerr << "Assert failed: " << msg << std::endl;
	std::cerr << file << " line " << lineNumber << msg << std::endl;
	exit(EXIT_FAILURE);
}

#endif /* _LIBWOLF_BENCHMARK_H */
