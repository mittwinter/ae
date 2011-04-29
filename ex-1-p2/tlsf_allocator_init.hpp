/* Author: Martin Wegner
 * Released under the terms of LGPL v3 (http://www.gnu.org/licenses/lgpl-3.0.txt).
 */
#pragma once
#ifndef TLSF_ALLOCATOR_INIT_HPP
#define TLSF_ALLOCATOR_INIT_HPP

#include <memory>
#include <new>
#include "tlsf.h"

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

		TLSFAllocator() throw() {
			tlsfPool = static_cast< void * >(new char[TLSF_POOL_SIZE]);
			init_memory_pool(TLSF_POOL_SIZE, tlsfPool);
		}

		TLSFAllocator(TLSFAllocator const &) throw() {}
		template< typename T1 > TLSFAllocator(TLSFAllocator< T1 > const &) throw() {}

		~TLSFAllocator() {
			destroy_memory_pool(tlsfPool);
			delete[] (static_cast< char * >(tlsfPool));
			tlsfPool = NULL;
		}

		pointer address(reference r) const { return &r; }
		const_pointer address(const_reference r) { return &r; }

		size_type max_size() const throw() { return (TLSF_POOL_SIZE / sizeof(T)); }

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
		//static unsigned int const TLSF_POOL_SIZE = 2 * 1024 * 1024 * 1024; // Bytes = 2 GiB
		static unsigned int const TLSF_POOL_SIZE = 1 * 1024 * 1024 * 1024; // Bytes = 1 GiB
		//static unsigned int const TLSF_POOL_SIZE = 256 * 1024 * 1024; // Bytes = 256 MiB

		void *tlsfPool;
};

template< typename T1, typename T2 > bool operator==(TLSFAllocator< T1 > const &, TLSFAllocator< T2 > const &) throw() {
       return false;
}
template< typename T1, typename T2 > bool operator!=(TLSFAllocator< T1 > const &, TLSFAllocator< T2 > const &) throw() {
       return true;
}

#endif

