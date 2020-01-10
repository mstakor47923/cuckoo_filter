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
	
	DynamicCuckooFilter::DynamicCuckooFilter(uint32_t bucketSize, uint32_t bucketNumber, uint32_t fingerPrintSize, uint32_t maxNumberOfKicks, CuckooHashing* hashingAlg)
		: _bucketSize(bucketSize), _bucketNumber(bucketNumber), _fingerPrintSize(fingerPrintSize), _maxNumberOfKicks(maxNumberOfKicks) {
		_hashing = hashingAlg;

		std::vector<CuckooFilter*>* cuckooFilters = new std::vector<CuckooFilter*>();
		cuckooFilters->push_back(new CuckooFilter(_bucketSize, _bucketNumber, _fingerPrintSize, _maxNumberOfKicks, _hashing));

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
		
	}

	bool DynamicCuckooFilter::remove(std::string val)
	{
		
	}

	bool DynamicCuckooFilter::insert(std::string val)
	{
		CuckooFilter* currentCuckooFilter = cuckooFilters->back();
		bool success = currentCuckooFilter->insert(val);
		if (!success) {
			cuckooFilters->push_back(new CuckooFilter(_bucketSize, _bucketNumber, _fingerPrintSize, _maxNumberOfKicks, _hashing));
			return cuckooFilters->back()->insert(val);
		}
	}
}