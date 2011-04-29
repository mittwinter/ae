#include <cstdlib>
#include <iostream>

#include "timing.h"

#include <vector>
#include "tlsf_util.hpp"
#include "tlsf_allocator.hpp"
#include "vector_const.hpp"
#include "vector_const_alloc.hpp"

const unsigned int NUMBER_OF_RUNS = 20 * 1000 * 1000;

int main(int argc, char *argv[]) {
	/*** std::vector ***/
	{
		std::cout << "std::vector:\t\t" << std::flush;
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

	/*** std::vector with TLSFAllocator ***/
	{
		tlsf::Util::init();
		std::cout << "std::vector w/ TLSF:\t" << std::flush;
		// Save start time:
		struct rusage start, stop;
		if(getrusage(RUSAGE_SELF, &start)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		{ // extra scope is needed since vector needs to be destroyed before call to tlsf::Util::destroy():
			std::vector< int, TLSFAllocator< int > > v;
			for(unsigned int i = 0; i < NUMBER_OF_RUNS; i++) {
				v.push_back(i);
			}
		}
		// Save end time
		if(getrusage(RUSAGE_SELF, &stop)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		std::cout << "Used time: " << timediff(start, stop) << " secs." << std::endl;
		tlsf::Util::destroy();
	}

	/*** vector_const ***/
	{
		std::cout << "vector_const:\t\t" << std::flush;
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

	/*** vector_const_tlsf ***/
	{
		tlsf::Util::init();
		std::cout << "vector_const_tlsf:\t" << std::flush;
		// Save start time:
		struct rusage start, stop;
		if(getrusage(RUSAGE_SELF, &start)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		{ // extra scope is needed since vector needs to be destroyed before call to tlsf::Util::destroy():
			vector_const_tlsf< int > v;
			for(unsigned int i = 0; i < NUMBER_OF_RUNS; i++) {
				v.push_back(i);
			}
		}
		// Save end time
		if(getrusage(RUSAGE_SELF, &stop)) {
			std::cerr << "getrusage() failed." << std::endl;
			return EXIT_FAILURE;
		}
		std::cout << "Used time: " << timediff(start, stop) << " secs." << std::endl;
		tlsf::Util::destroy();
	}

	return EXIT_SUCCESS;
}
