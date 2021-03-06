#include <iostream>

#include "sudoku.hpp"

int main() {
	Sudoku s2_solved( 2, (int [])
		{ 0, 2, 1, 3
		, 3, 1, 2, 0
		, 1, 3, 0, 2
		, 2, 0, 3, 1
		}
		);
	Sudoku s2( 2, (int [])
		{  0, -1, -1,  3
		, -1, -1,  2,  0
		,  1,  3, -1, -1
		, -1,  0, -1, -1
		}
		);
	Sudoku s3_solved( 3, (int [])
		{ 5, 6, 0, 7, 4, 8, 3, 1, 2
		, 8, 2, 3, 6, 1, 5, 4, 7, 0
		, 7, 4, 1, 2, 0, 3, 8, 5, 6
		, 1, 3, 5, 4, 8, 2, 6, 0, 7
		, 0, 8, 6, 1, 5, 7, 2, 4, 3
		, 4, 7, 2, 0, 3, 6, 5, 8, 1
		, 3, 5, 7, 8, 2, 0, 1, 6, 4
		, 2, 0, 4, 5, 6, 1, 7, 3, 8
		, 6, 1, 8, 3, 7, 4, 0, 2, 5
		}
		);
	Sudoku s3( 3, (int[])
		{  5,  6,  0, -1, -1, -1, -1, -1,  2
		,  8,  2,  3, -1,  1, -1,  4,  7,  0
		,  7, -1, -1, -1, -1,  3, -1,  5, -1
		, -1,  3, -1,  4,  8, -1,  6, -1, -1
		, -1,  8, -1, -1,  5, -1, -1,  4, -1
		, -1, -1,  2, -1, -1, -1, -1, -1, -1
		, -1,  5,  7, -1, -1,  0, -1,  6, -1
		, -1, -1, -1,  5, -1, -1, -1, -1, -1
		, -1,  1, -1, -1, -1,  4, -1,  2, -1
		}
		);

	s2_solved.solve();
	s2.solve();
	s3_solved.solve();
	s3.solve();

	std::clog << "s2_solved: " << (s2_solved.isSolved() ? 'y' : 'n') << std::endl;
	std::clog << "s2:        " << (s2.isSolved()        ? 'y' : 'n') << std::endl;
	std::clog << "s3_solved: " << (s3_solved.isSolved() ? 'y' : 'n') << std::endl;
	std::clog << "s3:        " << (s3.isSolved()        ? 'y' : 'n') << std::endl;

	return 0;
}
