#pragma once
#ifndef TOBIAS_HPP
#define TOBIAS_HPP

#include <iostream>
#include <string>
#include <vector>

class Tobias {
	public:
		Tobias( std::string const &filename );
		~Tobias() {}

		size_t slots() const { return getReference().size(); }
		std::vector< std::string > const &getNames() const { return names; }
		std::vector< bool > const &getReference() const { return reference; }
		std::vector< bool > const &getChoices() const { return choices; }
		std::vector< bool > const &getSchedule() const { return schedule; }

		void solve( size_t maxStudentsStart );
		bool isSolved( size_t max ) const;

	private:
		bool solve( size_t max, size_t slot, size_t student );
		bool slotFull( size_t slot, size_t max ) const;
		size_t avaiableSlots() const;
		bool isStudentScheduled( size_t student ) const;

		std::vector< std::string > names;
		std::vector< bool > reference;
		std::vector< bool > choices;

		std::vector< bool > schedule;
};

std::ostream &operator<<( std::ostream &out, Tobias const &t );

#endif

