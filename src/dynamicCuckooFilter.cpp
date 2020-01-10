#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <time.h>
#include <functional>

#include "dynamicCuckooFilter.hh"
#include "cuckooFilter.hh"
#include "cuckooConstants.hh"

namespace cuckoo {
	
	DynamicCuckooFilter::DynamicCuckooFilter(uint32_t bucketSize,
		uint32_t bucketNumber, uint32_t fingerPrintSize, uint32_t maxNumberOfKicks,
		CuckooHashing* hashingAlg)
		: _bucketSize(bucketSize), _bucketNumber(bucketNumber),
		_fingerPrintSize(fingerPrintSize), _maxNumberOfKicks(maxNumberOfKicks) {
		_hashing = hashingAlg;

		std::vector<CuckooFilter*>* cuckooFilters = new std::vector<CuckooFilter*>();
		cuckooFilters->push_back(new CuckooFilter(bucketSize, bucketNumber, fingerPrintSize, maxNumberOfKicks, hashingAlg));

		srand(time(NULL));
	}

	DynamicCuckooFilter::~DynamicCuckooFilter()
	{
		for (auto it = cuckooFilters->begin(); it != cuckooFilters->end(); it++) {
			delete (*it);
		}

		delete cuckooFilters;
	}

	bool DynamicCuckooFilter::lookup(std::string val)
	{
		for (auto it = cuckooFilters->begin(); it != cuckooFilters->end(); it++) {
			if ((*it)->lookup(val) == true){
				return true;
			}
		}
		return false;
	}

	bool DynamicCuckooFilter::remove(std::string val)
	{
		for (auto it = cuckooFilters->begin(); it != cuckooFilters->end(); it++) {
			if ((*it)->lookup(val) == true){
				(*it)->remove(val);
				return true;
			}
		}
		return false;
	}

	bool DynamicCuckooFilter::insert(std::string val)
	{
		
	}
}