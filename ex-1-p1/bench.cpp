#include <cstdlib>
#include <iostream>

#include "timing.h"

#include <vector>
#include "vector-sf.h"
#include "vector_const.hpp"

const unsigned int NUMBER_OF_RUNS = 100 * 1000 * 1000;

int main(int argc, char *argv[]) {
	/*** std::vector ***/
	{
		std::cout << "std::vector:\t" << std::flush;
		// Save start time:
		struct rusage start, stop;
		if(getrusage(RUSAGE_SELF, &start)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		std::vector< int > v;
		for(unsigned int i = 0; i < NUMBER_OF_RUNS; i++) {
			v.push_back(i);
		}
		// Save end time
		if(getrusage(RUSAGE_SELF, &stop)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		std::cout << "Used time: " << timediff(start, stop) << " secs." << std::endl;
	}

	/*** vec_array ***/
	{
		std::cout << "vec_array:\t" << std::flush;
		// Save start time:
		struct rusage start, stop;
		if(getrusage(RUSAGE_SELF, &start)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		vec_array< int > v;
		for(unsigned int i = 0; i < NUMBER_OF_RUNS; i++) {
			v.push_back(i);
		}
		// Save end time
		if(getrusage(RUSAGE_SELF, &stop)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		std::cout << "Used time: " << timediff(start, stop) << " secs." << std::endl;
	}

	/*** vec_alloc ***/
	{
		std::cout << "vec_alloc:\t" << std::flush;
		// Save start time:
		struct rusage start, stop;
		if(getrusage(RUSAGE_SELF, &start)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		vec_alloc< int > v;
		for(unsigned int i = 0; i < NUMBER_OF_RUNS; i++) {
			v.push_back(i);
		}
		// Save end time
		if(getrusage(RUSAGE_SELF, &stop)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		std::cout << "Used time: " << timediff(start, stop) << " secs." << std::endl;
	}

	/*** vec_realloc ***/
	{
		std::cout << "vec_realloc:\t" << std::flush;
		// Save start time:
		struct rusage start, stop;
		if(getrusage(RUSAGE_SELF, &start)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		vec_realloc< int > v;
		for(unsigned int i = 0; i < NUMBER_OF_RUNS; i++) {
			v.push_back(i);
		}
		// Save end time
		if(getrusage(RUSAGE_SELF, &stop)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		std::cout << "Used time: " << timediff(start, stop) << " secs." << std::endl;
	}

	/*** vector_const ***/
	{
		std::cout << "vector_const:\t" << std::flush;
		// Save start time:
		struct rusage start, stop;
		if(getrusage(RUSAGE_SELF, &start)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		vector_const< int > v;
		for(unsigned int i = 0; i < NUMBER_OF_RUNS; i++) {
			v.push_back(i);
		}
		// Save end time
		if(getrusage(RUSAGE_SELF, &stop)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		std::cout << "Used time: " << timediff(start, stop) << " secs." << std::endl;
	}

	return EXIT_SUCCESS;
}
