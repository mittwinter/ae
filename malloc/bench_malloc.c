#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "diff_timespec.h"

int main(int argc, char *argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Usage: %s <maxSize> <runs>\n", argv[0]);
		return EXIT_FAILURE;
	}
	printf("sizeof(unsigned long long)...: %ld\n", sizeof(unsigned long long));
	struct timespec res;
	clock_getres(CLOCK_PROCESS_CPUTIME_ID, &res);
	printf("process cputime clock resolution is...: %lu.%lu secs\n", res.tv_sec, res.tv_nsec);
	unsigned long long minSize = 16;
	unsigned long long maxSize = atoll(argv[1]);
	unsigned long long runs = atoll(argv[2]);
	printf("Benchmarking malloc() with sizes from %llu to %llu with %llu runs each...\n", minSize, maxSize, runs);

	unsigned long long size = 0;
	for(size = minSize; size <= maxSize; size *= 2) {
		double avgMallocRuntime = 0.0;
		unsigned long long i = 0;
		for(i = 0; i < runs; i++) {
			struct timespec startTime, endTime, diffTime;
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTime);
			void *ptr = malloc(size);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTime);
			memset(ptr, 42, size);
			free(ptr);
			ptr = NULL;
			diffTimespec(&startTime, &endTime, &diffTime);
			if(i > 0) {
				avgMallocRuntime = (avgMallocRuntime + (diffTime.tv_sec + ((double) diffTime.tv_nsec / 1000000000))) / 2;
			}
			else {
				avgMallocRuntime = diffTime.tv_sec + ((double) diffTime.tv_nsec / 1000000000);
			}
		}
		printf("malloc(%llu) avg:\t%.9f secs\n", size, avgMallocRuntime);
	}

	return EXIT_SUCCESS;
}

