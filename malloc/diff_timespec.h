#pragma once
#ifndef DIFF_TIMESPEC_H
#define DIFF_TIMESPEC_H

void diffTimespec(struct timespec *t1, struct timespec *t2, struct timespec *diff) {
	assert(t1->tv_sec < t2->tv_sec || (t1->tv_sec == t2->tv_sec && t1->tv_nsec <= t2->tv_nsec));
	diff->tv_sec = (t2->tv_sec - t1->tv_sec - 1) + (t2->tv_nsec + (1000000000 - t1->tv_nsec)) / 1000000000;
	diff->tv_nsec = (t2->tv_nsec + (1000000000 - t1->tv_nsec)) % 1000000000;
}

#endif

