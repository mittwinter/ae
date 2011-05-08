/* Author: Martin Wegner
 * Released under the terms of LGPL v3 (http://www.gnu.org/licenses/lgpl-3.0.txt).
 */
#pragma once
#ifndef NEW_ALLOCATOR_BENCH_HPP
#define NEW_ALLOCATOR_BENCH_HPP

#include <memory>
#include <new>
#include <time.h>

#include "diff_timespec.h"

template< typename T > class NewAllocator {
	public:
		typedef size_t size_type;
		typedef T * pointer;
		typedef T const * const_pointer;
		typedef T & reference;
		typedef T const & const_reference;
		typedef T value_type;

		template< typename T1 > struct rebind {
			typedef NewAllocator< T1 > other;
		};

		NewAllocator() throw() : avgAllocTime(0.0) {}

		NewAllocator(NewAllocator const &o) throw() {
			avgAllocTime = o.avgAllocTime;
		}
		template< typename T1 > NewAllocator(NewAllocator< T1 > const &) throw() {}

		~NewAllocator() {}

		pointer address(reference r) const { return &r; }
		const_pointer address(const_reference r) { return &r; }

		size_type max_size() const throw() { return (size_type(-1) / sizeof(T)); }

		pointer allocate(size_type n, void const * = NULL) {
			struct timespec startTime, endTime, diffTime;
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTime);
			pointer p = new T[n];
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTime);
			diffTimespec(&startTime, &endTime, &diffTime);
			if(avgAllocTime != 0.0) {
				avgAllocTime = (avgAllocTime + ((diffTime.tv_sec + ((double) diffTime.tv_nsec / 1000000000)) / n)) / 2;
			}
			else {
				avgAllocTime = (diffTime.tv_sec + ((double) diffTime.tv_nsec / 1000000000)) / n;
			}
			return p;
		}
		void deallocate(pointer p, size_type) {
			delete[] p;
		}
		void construct(pointer p, const_reference val) {
			new(static_cast< void * >(p)) T(val);
		}
		void destroy(pointer p) {
			p->~T();
		}

		double getAvgAllocTime() const { return avgAllocTime; }

	protected:
		double avgAllocTime;
};

template< typename T1, typename T2 > bool operator==(NewAllocator< T1 > const &, NewAllocator< T2 > const &) throw() {
       return false;
}
template< typename T1, typename T2 > bool operator!=(NewAllocator< T1 > const &, NewAllocator< T2 > const &) throw() {
       return true;
}

#endif
