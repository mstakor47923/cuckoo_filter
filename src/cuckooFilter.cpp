#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <time.h>
#include "cuckooFilter.hh"
#include "cuckooConstants.hh"

namespace cuckoo {
	
	CuckooFilter::CuckooFilter(uint32_t bucketSize, uint32_t bucketNumber, uint32_t fingerPrintSize, uint32_t maxNumberOfKicks, CuckooHashing* hashingAlg)
		: _bucketSize(bucketSize), _bucketNumber(bucketNumber), _fingerPrintSize(fingerPrintSize), _maxNumberOfKicks(maxNumberOfKicks) {
		_table = new std::map<uint32_t, std::vector<uint32_t>>();
		_hashing = hashingAlg;
		srand(time(NULL));
	}

	CuckooFilter::~CuckooFilter()
	{
		delete _table;
	}

	bool CuckooFilter::lookup(std::string val)
	{
		uint32_t f = fingerprint(val);
		uint32_t i = _hashing->getHash(val);
		uint32_t j = i ^ _hashing->getHash(f);

		auto bucket_i = _table->find(i);
		auto bucket_j = _table->find(j);

		if (bucket_i != _table->end() && 
			std::find(bucket_i->second.begin(), bucket_i->second.end(), f) != bucket_i->second.end()) {
			return true;
		}
		else if (bucket_j != _table->end() && 
				 std::find(bucket_j->second.begin(), bucket_j->second.end(), f) != bucket_j->second.end()) {
			return true;
		} else {
			return false;
		}
		return false;
	}

	bool CuckooFilter::remove(std::string val)
	{
		return false;
	}

	bool CuckooFilter::insert(std::string val)
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

		uint32_t i = rand()%2 ? i2 : i1;
		//for (uint32_t n=0; n < cuckoo::constants::maxNumberOfKicks)

		return false;
	}

	uint32_t CuckooFilter::fingerprint(std::string val)
	{
		return 0;
	}

}