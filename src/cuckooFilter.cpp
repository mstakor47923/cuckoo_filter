#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <time.h>
#include "cuckooFilter.hh"

namespace cuckoo {
	
	CuckooFilter::CuckooFilter(uint32_t bucketSize, uint32_t bucketNumber, uint32_t fingerPrintSize, CuckooHashing* hashingAlg)
		: _bucketSize(bucketSize), _bucketNumber(bucketNumber), _fingerPrintSize(fingerPrintSize) {
		_table = new std::map<uint32_t, std::vector<uint32_t>>();
		_hashing = hashingAlg;
		srand(time(NULL));
	}

	CuckooFilter::~CuckooFilter()
	{
		delete _table;
	}

	uint32_t CuckooFilter::lookup(uint32_t val)
	{
		return uint32_t();
	}

	bool CuckooFilter::remove(uint32_t val)
	{
		return false;
	}

	bool CuckooFilter::insert(uint32_t val)
	{
		uint32_t f = fingerprint(val);
		uint32_t i1 = _hashing->getHash(val);
		uint32_t i2 = i1 ^ _hashing->getHash(f);
		auto bucket1 = _table->at(i1);
		auto bucket2 = _table->at(i2);
		if (bucket1.size() < _bucketSize){
			bucket1.push_back(f);
			return true;
		}
		else if (bucket2.size() < _bucketSize){
			bucket2.push_back(f);
			return true;
		}

		

		
		return false;
	}

	uint32_t CuckooFilter::fingerprint(uint32_t val)
	{
		return 0;
	}

}