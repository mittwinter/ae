#include "const_vector.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
	vector_const< int > v;
	for(unsigned int i = 0; i < 1000000; i++) {
		v.push_back(i);
	}
	return EXIT_SUCCESS;
}
