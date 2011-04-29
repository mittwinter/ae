/* Author: Martin Wegner
 * Released under the terms of LGPL v3 (http://www.gnu.org/licenses/lgpl-3.0.txt).
 */
#pragma once
#ifndef CONST_VECTOR_HPP
#define CONST_VECTOR_HPP

#include <cassert>
#include <stdint.h>

template< typename T > class vector_const {
	public:
		vector_const() : capacity(1), used(0), toCopy(0), container(new T[1]), nextContainer(new T[2 * 1]) {}
		virtual ~vector_const() {
			delete[] container;
			delete[] nextContainer;
		}

		void push_back(T const &e) {
			assert(toCopy <= used);
			assert(used < capacity);
			// Incrementally copy elements from container to nextContainer:
			nextContainer[toCopy] = container[toCopy];
			++toCopy;
			// Actually push back new element to both containers:
			container[used] = e;
			nextContainer[used] = e;
			++used;
			if(used == capacity) {
				delete[] container;
				container = nextContainer;
				capacity *= 2;
				nextContainer = new T[2 * capacity];
				toCopy = 0;
			}
		}

		void pop_back() { --used; }

		T const &get(uint64_t p) const {
			assert(p < used);
			return container[p];
		}
		void set(uint64_t p, T const &e) {
			assert(p < size);
			container[p] = e;
		}
		uint64_t size() const { return used; }

	protected:
		uint64_t capacity;
		uint64_t used;
		uint64_t toCopy;
		T *container;
		T *nextContainer;
};

#endif

