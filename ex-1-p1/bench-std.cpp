#include <cstdlib>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
	std::vector< int > v;
	for(unsigned int i = 0; i < 1000000; i++) {
		v.push_back(i);
	}
	return EXIT_SUCCESS;
}
