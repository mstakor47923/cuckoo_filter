#ifndef DYNAMIC_CUCKOO_FILTER_HH
#define DYNAMIC_CUCKOO_FILTER_HH

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdint.h>

#include "cuckooFilter.hh"
#include "cuckooHashing.hh"

namespace cuckoo {

	class DynamicCuckooFilter {
	private:
		uint32_t _bucketSize, _bucketNumber, _fingerPrintSize, _maxNumberOfKicks;
		std::vector<CuckooFilter*>* cuckooFilters;
		CuckooHashing* _hashing;

	public:
		DynamicCuckooFilter(
			uint32_t bucketSize, uint32_t bucketNumber,
			uint32_t fingerPrintSize, uint32_t maxNumberOfKicks,
			CuckooHashing* hashingAlg);
		~DynamicCuckooFilter();

		bool lookup(std::string val);
		bool remove(std::string val);
		bool insert(std::string val);

	private:
		uint32_t fingerprint(std::string val);
	};
}

#endif // !CUCKOO_FILTER_HH
