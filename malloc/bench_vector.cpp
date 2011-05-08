#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <time.h>
#include <vector>

#include "diff_timespec.h"
#include "new_allocator_bench.hpp"

int main(int argc, char *argv[]) {
	if(argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <maxSize> <runs>" << std::endl;
		return EXIT_FAILURE;
	}
	struct timespec res;
	clock_getres(CLOCK_PROCESS_CPUTIME_ID, &res);
	std::clog << "process cputime clock resolution is...: " << res.tv_sec << "." << std::setw(9) << std::setfill('0') << res.tv_nsec << " secs" << std::endl;
	uint64_t minSize = 16;
	uint64_t maxSize = 0;
	uint64_t runs = 0;
	std::stringstream sstrArg;
	sstrArg.clear();
	sstrArg.str(argv[1]);
	sstrArg >> maxSize;
	sstrArg.clear();
	sstrArg.str(argv[2]);
	sstrArg >> runs;
	std::clog << "Benchmarking std::vector< unsigned int > with sizes from " << minSize << " to " << maxSize << " elements with " << runs << " runs each..." << std::endl;

	for(uint64_t size = minSize; size <= maxSize; size *= 2) {
		double avgVectorRuntime = 0.0;
		double avgAllocTime = 0.0;
		for(uint64_t i = 0; i < runs; i++) {
			struct timespec startTime, endTime, diffTime;
			std::vector< unsigned int, NewAllocator< unsigned int > > v;
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTime);
			for(unsigned int e = 0; e < size; e++) {
				v.push_back(e);
			}
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTime);
			diffTimespec(&startTime, &endTime, &diffTime);
			if(i > 0) {
				avgVectorRuntime = (avgVectorRuntime + (diffTime.tv_sec + ((double) diffTime.tv_nsec / 1000000000))) / 2;
				avgAllocTime = (avgAllocTime + v.get_allocator().getAvgAllocTime()) / 2;
			}
			else {
				avgVectorRuntime = diffTime.tv_sec + ((double) diffTime.tv_nsec / 1000000000);
				avgAllocTime = v.get_allocator().getAvgAllocTime();
			}
		}
		std::clog << "std::vector< unsigned int >::size() = " << size << std::endl;
		std::clog << "\t avg: " << std::fixed << std::setprecision(9) << avgVectorRuntime << " secs" << std::endl;
		std::clog << "\t avg per element: " << std::fixed << std::setprecision(9) << (avgVectorRuntime / size) << " secs" << std::endl;
		std::clog << "\t avg per allocation element: " << std::fixed << std::setprecision(9) << avgAllocTime << " secs" << std::endl;
	}

	return EXIT_SUCCESS;
}

