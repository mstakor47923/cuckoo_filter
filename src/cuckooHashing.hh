#ifndef CUCKOO_HASHING_HH
#define CUCKOO_HASHING_HH

#include <iostream>
#include <stdint.h>

namespace cuckoo {

	class CuckooHashing {
	public:
		CuckooHashing();
		uint32_t getHash(const uint32_t val);
	};
}

#endif // !CUCKOO_HASHING_HH