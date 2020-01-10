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
		_cuckooFilters = new std::vector<Filter*>();
		_cuckooFilters->push_back(new CuckooFilter(_bucketSize, _bucketNumber, _fingerPrintSize, _maxNumberOfKicks, _hashing));
		srand(time(NULL));
	}

	DynamicCuckooFilter::~DynamicCuckooFilter()
	{
		for (auto it = _cuckooFilters->begin(); it != _cuckooFilters->end(); it++) {
			delete (*it);
		}

		delete _cuckooFilters;
	}

	bool DynamicCuckooFilter::lookup(std::string val)
	{
		for (auto it = _cuckooFilters->begin(); it != _cuckooFilters->end(); it++) {
			if ((*it)->lookup(val) == true){
				return true;
			}
		}

		return false;
	}

	bool DynamicCuckooFilter::remove(std::string val)
	{
		for (auto it = _cuckooFilters->begin(); it != _cuckooFilters->end(); it++) {
			if ((*it)->lookup(val) == true){
				(*it)->remove(val);
				return true;
			}
		}

		return false;
	}

	bool DynamicCuckooFilter::insert(std::string val)
	{
		auto currentCuckooFilter = _cuckooFilters->back();
		bool success = currentCuckooFilter->insert(val);
		if (!success) {
			_cuckooFilters->push_back(new CuckooFilter(_bucketSize, _bucketNumber, _fingerPrintSize, _maxNumberOfKicks, _hashing));
			return _cuckooFilters->back()->insert(val);
		}

		return success;
	}

	uint32_t DynamicCuckooFilter::getCalculatedMemoryUsage() {
		uint32_t totSize = 0;
		for (auto it = _cuckooFilters->begin(); it != _cuckooFilters->end(); it++) {
			totSize += (*it)->getCalculatedMemoryUsage();
		}

		return totSize;
	}
}