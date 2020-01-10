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

	class DynamicCuckooFilter : public Filter {
	private:
		uint32_t _bucketSize, _bucketNumber, _fingerPrintSize, _maxNumberOfKicks;
		CuckooHashing* _hashing;
		std::vector<Filter*>* _cuckooFilters;

	public:
		DynamicCuckooFilter(
			uint32_t bucketSize, uint32_t bucketNumber,
			uint32_t fingerPrintSize, uint32_t maxNumberOfKicks,
			CuckooHashing* hashingAlg);
		~DynamicCuckooFilter();

		virtual bool lookup(std::string val);
		virtual bool remove(std::string val);
		virtual bool insert(std::string val);
	private:
		uint32_t fingerprint(std::string val);
	};
}

#endif // !CUCKOO_FILTER_HH
