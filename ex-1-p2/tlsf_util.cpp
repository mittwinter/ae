#include "tlsf_util.hpp"

#include "tlsf.h"

namespace tlsf {

void *Util::tlsfPool = NULL;

void Util::init() {
	if(tlsfPool == NULL) {
		tlsfPool = static_cast< void * >(new char[TLSF_POOL_SIZE]);
		init_memory_pool(TLSF_POOL_SIZE, tlsfPool);
	}
}

void Util::destroy() {
	destroy_memory_pool(tlsfPool);
	delete[] (static_cast< char * >(tlsfPool));
	tlsfPool = NULL;
}

}
