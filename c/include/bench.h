#ifndef _WOLFLIB_BENCHMARK_H
#define _WOLFLIB_BENCHMARK_H

#include <time.h>

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


#endif /* _WOLFLIB_BENCHMARK_H */
