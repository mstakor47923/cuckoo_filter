#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <time.h>
#include <functional>
#include "cuckooHashing.hh"

#include "efficientCuckooFilter.hh"
#include "cuckooFilter.hh"
#include "cuckooConstants.hh"

namespace cuckoo {
	
	EfficientCuckooFilter::EfficientCuckooFilter(uint32_t bucketSize,
		uint32_t bucketNumber, uint32_t fingerPrintSize, uint32_t maxNumberOfKicks,
		CuckooHashing* hashingAlg)
		: _bucketSize(bucketSize), _bucketNumber(bucketNumber),
		_fingerPrintSize(fingerPrintSize), _maxNumberOfKicks(maxNumberOfKicks) {

		_hashing = hashingAlg;
		_filter = new cuckoofilter::CuckooFilter<__int128_t, 16>(_bucketSize * _bucketNumber);
	}

	EfficientCuckooFilter::~EfficientCuckooFilter() { }

	bool EfficientCuckooFilter::lookup(std::string val) {
		auto f = fingerprint(val);
		auto status = _filter->Contain(f);
        return status == cuckoofilter::Ok;
	}

	bool EfficientCuckooFilter::remove(std::string val) {
		auto f = fingerprint(val);
		auto status = _filter->Delete(f);
        return status == cuckoofilter::Ok;
	}

	bool EfficientCuckooFilter::insert(std::string val) {
		auto f = fingerprint(val);
		auto status = _filter->Add(f);
        return status == cuckoofilter::Ok;
	}

	uint32_t EfficientCuckooFilter::getCalculatedMemoryUsage() {
		return _filter->SizeInBytes();
	}

	uint32_t EfficientCuckooFilter::fingerprint(std::string val) {
		std::hash<std::string> hasher;
		auto hashVal = hasher(val);
		for (auto it=val.begin(); it<val.end(); ++it)
		{

		}
		return hashVal;
	}
}