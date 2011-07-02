#include <fstream>
#include <sstream>

#include "tobias.hpp"

Tobias::Tobias( std::string const &filename ) {
	std::ifstream in( filename.c_str() );
	std::string line;
	std::stringstream sstr;
	std::string name;

	while( in.good() ) {
		sstr.clear();

		getline( in, line );
		sstr.str(line);
		sstr >> name;

		if( name == "end" ) {
			break;
		}
		if( name != "Tobias" ) {
			names.push_back( name );
		}

		while( sstr.good() ) {
			bool choice;
			sstr >> choice;
			if( name == "Tobias" ) {
				reference.push_back( choice );
			}
			else {
				choices.push_back( choice );
			}
		}
	}
	in.close();
	schedule.resize( choices.size(), false );
}

void Tobias::solve( size_t maxStudentsStart ) {
	//for( size_t maxStudents = getNames().size() / 4; maxStudents <= getNames().size(); maxStudents++ ) {
	for( size_t maxStudents = maxStudentsStart; maxStudents <= getNames().size(); maxStudents++ ) {
		std::clog << "max = " << maxStudents << "..." << std::endl;
		if( solve( maxStudents, 0, 0 ) ) {
			std::clog << "Found solution for max = " << maxStudents << "!" << std::endl;
			break;
		}
	}
}

bool Tobias::isSolved( size_t max ) const {
	// Each student assigned to exactly one slot:
	for( size_t s = 0; s < getNames().size(); s++ ) {
		size_t count = 0;
		for( size_t i = 0; i < slots(); i++ ) {
			if( schedule.at( s * slots() + i ) ) {
				count++;
			}
		}
		if( count != 1 ) {
			return false;
		}
	}
	// Each slot at most max students:
	for( size_t i = 0; i < slots(); i++ ) {
		size_t count = 0;
		for( size_t s = 0; s < getNames().size(); s++ ) {
			if( schedule.at( s * slots() + i ) ) {
				count++;
			}
		}
		if( count > max ) {
			return false;
		}
	}
	return true;
}

bool Tobias::solve( size_t max, size_t slot, size_t student ) {
	//std::clog << slot << "," << student << "..." << std::endl;
	if( student == getNames().size() ) {
		slot++;
		student = 0;
	}
	if( avaiableSlots() == 0 || slot >= slots() ) {
		//std::cerr << (*this) << std::endl;
		return isSolved( max );
	}
	//std::clog << "!" << !slotFull( slot, max ) << std::endl;
	//std::clog << ">" << getChoices().at( student * slots() + slot ) << std::endl;
	//std::clog << "+" << !isStudentScheduled( student ) << std::endl;
	if( getReference().at( slot ) && !slotFull( slot, max ) && getChoices().at( student * slots() + slot ) && !isStudentScheduled( student ) ) {
		schedule[ student * slots() + slot ] = true;
		//std::clog << "Trying schedule[" << student << "," << slot << "] = true..." << std::endl;
		if( solve( max, slot, student + 1 ) ) {
			return true;
		}
		schedule[ student * slots() + slot ] = false;
	}
//	else {
		return solve( max, slot, student + 1 );
//	}
	return false;
}

bool Tobias::slotFull( size_t slot, size_t max ) const {
	size_t count = 0;
	for( size_t i = slot; slot < schedule.size(); slot += slots() ) {
		if( schedule.at( i ) ) {
			count++;
		}
	}
	return (count == max);
}

size_t Tobias::avaiableSlots() const {
	size_t available = 4;
	for( size_t i = 0; i < slots(); i++ ) {
		for( size_t s = 0; s < getNames().size(); s++ ) {
			if( schedule.at( s * slots() + i ) ) {
				available--;
				break;
			}
		}
		if( available == 0 ) {
			break;
		}
	}
	//std::clog << "avail: " << available << std::endl;
	return available;
}

bool Tobias::isStudentScheduled( size_t student ) const {
	bool scheduled = false;
	for( size_t i = student * slots(); i < (student + 1) * slots(); i++ ) {
		if( schedule.at( i ) ) {
			scheduled = true;
			break;
		}
	}
	return scheduled;
}

std::ostream &operator<<( std::ostream &out, Tobias const &t ) {
	out << "Tobias:\t" << std::flush;
	for( size_t i = 0; i < t.slots(); i++ ) {
		out << " " << t.getReference().at( i ) << std::flush;
	}
	out << std::endl;
	out << "Choices:" << std::endl;
	for( size_t i = 0; i < t.getNames().size(); i++ ) {
		out << t.getNames().at( i ) << ":\t" << std::flush;
		for( size_t j = 0; j < t.slots(); j++ ) {
			out << " " << t.getChoices().at( i * t.slots() + j ) << std::flush;
		}
		out << std::endl;
	}
	out << "Solution:" << std::endl;
	for( size_t i = 0; i < t.getNames().size(); i++ ) {
		out << t.getNames().at( i ) << ":\t" << std::flush;
		for( size_t j = 0; j < t.slots(); j++ ) {
			out << " " << t.getSchedule().at( i * t.slots() + j ) << std::flush;
		}
		out << std::endl;
	}
	return out;
}
