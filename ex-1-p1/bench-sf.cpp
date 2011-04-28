#include "vector-sf.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
	vec_realloc< int > v;
	for(unsigned int i = 0; i < 1000000; i++) {
		v.push_back(i);
	}
	return EXIT_SUCCESS;
}
