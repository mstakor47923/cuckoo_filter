#ifndef CUCKOO_FILTER_HH
#define CUCKOO_FILTER_HH

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdint.h>

#include "cuckooHashing.hh"

namespace cuckoo {

	namespace constants {
		const uint32_t emptyEntry = 0;
	}

	class CuckooFilter {
	private:
		uint32_t _bucketSize, _fingerPrintSize, _bucketNumber;
		std::map<uint32_t, std::vector<uint32_t>>* _table;
		CuckooHashing* _hashing;

	public:
		CuckooFilter(uint32_t bucketSize, uint32_t bucketNumber, uint32_t fingerPrintSize, CuckooHashing* hashingAlg);
		~CuckooFilter();

		uint32_t lookup(std::string val);
		bool remove(std::string val);
		bool insert(std::string val);

	private:
		uint32_t fingerprint(std::string val);
	};
}

#endif // !CUCKOO_FILTER_HH
