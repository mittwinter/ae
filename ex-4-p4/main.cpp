#include <cstdlib>
#include <iostream>

#include "tobias.hpp"

int main( int argc, char *argv[] ) {
	if( argc < 2 || argc > 3 ) {
		std::cerr << argv[0] << " <file> [<maxStudentsStart>]" << std::endl;
		return EXIT_FAILURE;
	}
	Tobias t( argv[1] );
	t.solve( argc == 3 ? atoi(argv[2]) : 4 );
	std::cout << t;
	return EXIT_SUCCESS;
}
