#pragma once
#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <algorithm>
#include <iostream>

class Sudoku {
	public:
		Sudoku( int k, int *d );
		~Sudoku();

		int &operator()( int i, int j );
		int const &operator()( int i, int j ) const;
		bool isWritable( int i, int j ) const;
		void set( int i, int j, int v );

		int getK() const { return k; }
		int size() const { return k * k; }

		bool isSolved();

		void solve();

	private:
		typedef std::pair< int, bool > Entry;
		int k;
		Entry **data;
		bool **writable;

		bool solveBacktracking(int row, int col);
};

std::ostream &operator<<(std::ostream &out, Sudoku const &s);

#endif

