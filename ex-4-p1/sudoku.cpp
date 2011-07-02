#include <iostream>
#include <cassert>
#include <string>

#include "sudoku.hpp"

Sudoku::Sudoku( int k, int * d ) : k( k ) {
	data = new Entry *[ size() ];
	for( int i = 0; i < size(); i++ ) {
		data[ i ] = new Entry[ size() ];
	}

	for( int row = 0; row < size(); row++ ) {
		for( int col = 0; col < size(); col++ ) {
			data[ row ][ col ] = std::make_pair( d[ (row * k * k) + col ], (d[ (row * k * k) + col ] < 0) );
		}
	}
}

Sudoku::~Sudoku() {
	for( int i = 0; i < size(); i++ ) {
		delete[] data[ i ];
	}
	delete[] data;
}

int &Sudoku::operator()( int i, int j ) {
	assert( i >= 0 && i < size() );
	assert( j >= 0 && j < size() );
	return data[ i ][ j ].first;
}

int const &Sudoku::operator()( int i, int j ) const {
	assert( i >= 0 && i < size() );
	assert( j >= 0 && j < size() );
	return data[ i ][ j ].first;
}

bool Sudoku::isWritable( int i, int j ) const {
	assert( i >= 0 && i < size() );
	assert( j >= 0 && j < size() );
	return data[ i ][ j ].second;
}

void Sudoku::set( int i, int j, int v ) {
	assert( i >= 0 && i < size() );
	assert( j >= 0 && j < size() );
	assert( data[ i ][ j ].second );
	data[ i ][ j ].first = v;
}


bool Sudoku::isSolved() {
	// rows?
	for( int row = 0; row < size(); row++ ) {
		for( int val = 0; val < size(); val++ ) {
			int count = 0;
			for( int col = 0; col < size(); col++ ) {
				if( data[ row ][ col ].first == val ) {
					++count;
				}
			}
			if( count != 1 ) {
				return false;
			}
		}
	}

	// cols?
	for( int col = 0; col < size(); col++ ) {
		for( int val = 0; val < size(); val++ ) {
			int count = 0;
			for( int row = 0; row < size(); row++ ) {
				if( data[ row ][ col ].first == val ) {
					++count;
				}
			}
			if( count != 1 ) {
				return false;
			}
		}
	}

	// blocks?
	for( int brow = 0; brow < size(); brow += k ) {
		for( int bcol = 0; bcol < size(); bcol += k ) {
			for( int val = 0; val < size(); val++ ) {
				int count=0;
				for( int row = 0; row < k; row++ ) {
					for( int col = 0; col < k; col++ ) {
						if( data[ brow + row ][ bcol + col ].first == val ) {
							++count;
						}
					}
				}
				if( count != 1 ) {
					return false;
				}
			}
		}
	}

	return true;
}

void Sudoku::solve() {
	std::clog << "Ich weiss nicht, wie man " << getK() << "-Sudokus loest, dieses auch nicht:" << std::endl;
	std::cout << *this << std::endl;

	if(solveBacktracking( 0, 0 )) {
		std::clog << "Aber ich hab's doch geschafft!!1!" << std::endl;
	}
	std::cout << *this << std::endl;
}

bool Sudoku::solveBacktracking( int row, int col ) {
	if( col >= size() ) {
		row += 1;
		col = 0;
	}
	if( row >= size() ) {
		return isSolved();
	}
	if( !isWritable( row, col ) ) {
		return solveBacktracking( row, col + 1 );
	}
	for( int v = 0; v < size(); v++ ) {
		// check if value v is possible:
		bool isPossibleValue = true;
		// row:
		for( int c = 0; isPossibleValue && c < size(); c++ ) {
			if( (*this)( row, c ) == v ) {
				isPossibleValue = false;
			}
		}
		// col:
		for( int r = 0; isPossibleValue && r < size(); r++ ) {
			if( (*this)( r, col ) == v ) {
				isPossibleValue = false;
			}
		}
		// block:
		int r = row / k * k;
		int c = col / k * k;
		for( int i = 0; isPossibleValue && i < k; i++ ) {
			for( int j = 0 ; isPossibleValue && j < k; j++ ) {
				if( (*this)( r + i, c + j ) == v) {
					isPossibleValue = false;
				}
			}
		}
		if(isPossibleValue) {
			set( row, col, v );
			// recurse:
			if( solveBacktracking( row, col + 1 ) ) {
				return true;
			}
			set( row, col, -1);
		}
	}
	return false;
}

std::ostream &operator<<(std::ostream &out, Sudoku const &s) {
	for( int row = 0; row < s.size(); row++ ) {
		out << "\t" << std::flush;
		for( int col = 0; col < s.size(); col++ ) {
			out << " " << ( s( row, col ) >= 0 ? " " : "" ) << s( row, col );
		}
		std::cout << std::endl;
	}
	return out;
}
