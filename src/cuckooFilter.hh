#ifndef CUCKOO_FILTER_HH
#define CUCKOO_FILTER_HH

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdint.h>

#include "cuckooHashing.hh"
#include "filter.hh"

namespace cuckoo {

	class CuckooFilter : public Filter {
	private:
		uint32_t _bucketSize, _bucketNumber, _fingerPrintSize, _maxNumberOfKicks;
		std::hash<std::string> hasher;
		std::map<uint32_t, std::vector<uint32_t>*>* _table;
		CuckooHashing* _hashing;

	public:
		CuckooFilter(uint32_t bucketSize, uint32_t bucketNumber, uint32_t fingerPrintSize, uint32_t maxNumberOfKicks, CuckooHashing* hashingAlg);
		~CuckooFilter();

		virtual bool lookup(std::string val);
		virtual bool remove(std::string val);
		virtual bool insert(std::string val);
	private:
		uint32_t fingerprint(std::string val);
	};
}

#endif // !CUCKOO_FILTER_HH
