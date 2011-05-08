/* Author: Martin Wegner
 * Released under the terms of LGPL v3 (http://www.gnu.org/licenses/lgpl-3.0.txt).
 */
#pragma once
#ifndef TLSF_UTIL_HPP
#define TLSF_UTIL_HPP

#include <stddef.h> // size_t

namespace tlsf {

class Util {
	public:
		static size_t const TLSF_POOL_SIZE = 3 * 1024 * 1024 * 1024UL; // Bytes = 3 GiB

		static void init();
		static void destroy();

	protected:
		static void *tlsfPool;
};

}

#endif

