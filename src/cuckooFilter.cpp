#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <time.h>
#include <functional>

#include "cuckooFilter.hh"
#include "cuckooConstants.hh"

namespace cuckoo {
	
	CuckooFilter::CuckooFilter(uint32_t bucketSize, uint32_t bucketNumber, uint32_t fingerPrintSize, uint32_t maxNumberOfKicks, CuckooHashing* hashingAlg)
		: _bucketSize(bucketSize), _bucketNumber(bucketNumber), _fingerPrintSize(fingerPrintSize), _maxNumberOfKicks(maxNumberOfKicks) {
		
		_table = new std::vector<std::vector<uint32_t>*>(_bucketNumber, nullptr);
		//_table = new std::unordered_map<uint32_t, std::vector<uint32_t>*>();
		for (uint32_t i = 0; i < _bucketNumber; i++) {
			auto vec = new std::vector<uint32_t>();
			vec->reserve(_bucketSize);
			_table->at(i) = vec;
		}

		for (int i = 0; i < _fingerPrintSize; i++) {
			_mask.set(i, true);
		}

		_hashing = hashingAlg;
		srand(time(NULL));
	}

	CuckooFilter::~CuckooFilter()
	{
		for (uint32_t i =0; i< _bucketNumber; ++i)
			delete _table->at(i);
		delete _table;
	}

	bool CuckooFilter::lookup(std::string val) 
	{
		uint32_t f = fingerprint(val);
		uint32_t i = _hashing->getHash(val);
		uint32_t j = (i ^ _hashing->getHash(f)) % _bucketNumber;

		auto bucket_i = _table->at(i);
		auto bucket_j = _table->at(j);

		if (std::find(bucket_i->begin(), bucket_i->end(), f) != bucket_i->end()) {
			return true;
		}
		else if (std::find(bucket_j->begin(), bucket_j->end(), f) != bucket_j->end()) {
			return true;
		} else {
			return false;
		}
		return false;
	}

	bool CuckooFilter::remove(std::string val)
	{
		uint32_t f = fingerprint(val);
		uint32_t i = _hashing->getHash(val);
		uint32_t j = (i ^ _hashing->getHash(f)) % _bucketNumber;

		auto bucket_i = _table->at(i);
		auto bucket_j = _table->at(j);

		if (std::find(bucket_i->begin(), bucket_i->end(), f) != bucket_i->end()) {
			bucket_i->erase(std::remove(bucket_i->begin(), bucket_i->end(), f), bucket_i->end());
			return true;
		}
		else if (std::find(bucket_j->begin(), bucket_j->end(), f) != bucket_j->end()) {
			bucket_j->erase(std::remove(bucket_j->begin(), bucket_j->end(), f), bucket_j->end());
			return true;
		} else {
			return false;
		}

		return false;
	}

	bool CuckooFilter::insert(std::string val)
	{
		uint32_t f = fingerprint(val);
		uint32_t i1 = _hashing->getHash(val);
		uint32_t i2 = (i1 ^ _hashing->getHash(f)) % _bucketNumber;

		auto bucket1 = _table->at(i1);
		auto bucket2 = _table->at(i2);

		if (bucket1->size() < _bucketSize){
			bucket1->push_back(f);
			return true;
		}
		else if (bucket2->size() < _bucketSize){
			bucket2->push_back(f);
			return true;
		}

		auto i = rand() % 2 ? i2 : i1;

		for (uint32_t n = 0; n < _maxNumberOfKicks; n++){
			auto bucket = _table->at(i);
			uint32_t randIndex = rand() % bucket->size();
			auto temp = bucket->at(randIndex);
			bucket->at(randIndex) = f;
			f = temp;
			i = (i1 ^ _hashing->getHash(f)) % _bucketNumber;
			bucket = _table->at(i);
			if (bucket->size() < _bucketSize){
				bucket->push_back(f);
				return true;
			}
		}

		return false;
	}

	uint32_t CuckooFilter::getCalculatedMemoryUsage() {
		//uint32_t keySize = _table->size() * sizeof(uint32_t);
		uint32_t valSize = _table->size() * (sizeof(uint32_t) * _bucketSize);

		return valSize;
	}

	uint32_t CuckooFilter::fingerprint(std::string val) {
		auto hashVal = hasher(val) & (uint32_t)_mask.to_ulong();
		return hashVal;
	}

}