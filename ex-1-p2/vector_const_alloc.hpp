/* Author: Martin Wegner
 * Released under the terms of LGPL v3 (http://www.gnu.org/licenses/lgpl-3.0.txt).
 */
#pragma once
#ifndef VECTOR_CONST_ALLOC_HPP
#define VECTOR_CONST_ALLOC_HPP

#include <cassert>
#include <stddef.h> // size_t
#include "tlsf.h"

template< typename T > class vector_const_tlsf {
	public:
		typedef size_t size_type;

		vector_const_tlsf() : capacity(1), used(0), toCopy(0) {
			container = static_cast< T * >(tlsf_malloc(1 * sizeof(T)));
			nextContainer = static_cast< T * >(tlsf_malloc(2 * sizeof(T)));
		}
		virtual ~vector_const_tlsf() {
			tlsf_free(container);
			tlsf_free(nextContainer);
		}

		void push_back(T const &e) {
			assert(toCopy <= used);
			assert(used < capacity);
			// Incrementally copy elements from container to nextContainer:
			if(toCopy <= (used - 1)) {
				nextContainer[toCopy] = container[toCopy];
				++toCopy;
			}
			// Actually push back new element to both containers:
			container[used] = e;
			nextContainer[used] = e;
			++used;
			if(used == capacity) {
				tlsf_free(static_cast< void * >(container));
				container = nextContainer;
				capacity *= 2;
				nextContainer = static_cast< T * >(tlsf_malloc(2 * capacity * sizeof(T)));
				toCopy = 0;
			}
		}
		void pop_back() { --used; }

		T const &get(size_type p) const {
			assert(p < used);
			return container[p];
		}
		void set(size_type p, T const &e) {
			assert(p < size);
			container[p] = e;
		}
		size_type size() const { return used; }

	protected:
		size_type capacity;
		size_type used;
		size_type toCopy;

		T *container;
		T *nextContainer;
};

#endif

