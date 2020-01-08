#ifndef CUCKOO_HASHING_HH
#define CUCKOO_HASHING_HH

#include <iostream>
#include <stdint.h>

namespace cuckoo {

	class CuckooHashing {
	public:
		CuckooHashing(int maxHashNum);
		uint32_t getHash(const std::string val);
		uint32_t getHash(const uint32_t val);
	private:
		int _maxHashNum;
	};
}

#endif // !CUCKOO_HASHING_HH