/* Author: Martin Wegner
 * Released under the terms of LGPL v3 (http://www.gnu.org/licenses/lgpl-3.0.txt).
 */
#pragma once
#ifndef TLSF_ALLOCATOR_HPP
#define TLSF_ALLOCATOR_HPP

#include <memory>
#include <new>
#include "tlsf.h"
#include "tlsf_util.hpp"

template< typename T > class TLSFAllocator {
	public:
		typedef size_t size_type;
		typedef T * pointer;
		typedef T const * const_pointer;
		typedef T & reference;
		typedef T const & const_reference;
		typedef T value_type;

		template< typename T1 > struct rebind {
			typedef TLSFAllocator< T1 > other;
		};

		TLSFAllocator() throw() {}

		TLSFAllocator(TLSFAllocator const &) throw() {}
		template< typename T1 > TLSFAllocator(TLSFAllocator< T1 > const &) throw() {}

		~TLSFAllocator() {}

		pointer address(reference r) const { return &r; }
		const_pointer address(const_reference r) { return &r; }

		size_type max_size() const throw() { return (tlsf::Util::TLSF_POOL_SIZE / sizeof(T)); }

		pointer allocate(size_type n, void const * = NULL) {
			return static_cast< pointer >(tlsf_malloc(n * sizeof(T)));
		}
		void deallocate(pointer p, size_type) {
			tlsf_free(static_cast< void * >(p));
		}
		void construct(pointer p, const_reference val) {
			new(static_cast< void * >(p)) T(val);
		}
		void destroy(pointer p) {
			p->~T();
		}

	protected:
};

template< typename T1, typename T2 > bool operator==(TLSFAllocator< T1 > const &, TLSFAllocator< T2 > const &) throw() {
       return false;
}
template< typename T1, typename T2 > bool operator!=(TLSFAllocator< T1 > const &, TLSFAllocator< T2 > const &) throw() {
       return true;
}

#endif
