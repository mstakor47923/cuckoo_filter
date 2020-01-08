#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <time.h>
#include <functional>

#include "cuckooFilter.hh"
#include "cuckooConstants.hh"

namespace cuckoo {
	
	CuckooFilter::CuckooFilter(uint32_t bucketSize, uint32_t bucketNumber, uint32_t fingerPrintSize, uint32_t maxNumberOfKicks, CuckooHashing* hashingAlg)
		: _bucketSize(bucketSize), _bucketNumber(bucketNumber), _fingerPrintSize(fingerPrintSize), _maxNumberOfKicks(maxNumberOfKicks) {
		_table = new std::map<uint32_t, std::vector<uint32_t>*>();
		for (uint32_t i = 0; i < _bucketNumber; i++) {
			_table->insert(std::pair<uint32_t, std::vector<uint32_t>*>(i, new std::vector<uint32_t>()));
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
		uint32_t j = i ^ _hashing->getHash(f);

		auto bucket_i = _table->find(i);
		auto bucket_j = _table->find(j);

		if (bucket_i != _table->end() && 
			std::find(bucket_i->second->begin(), bucket_i->second->end(), f) != bucket_i->second->end()) {
			return true;
		}
		else if (bucket_j != _table->end() && 
				 std::find(bucket_j->second->begin(), bucket_j->second->end(), f) != bucket_j->second->end()) {
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
		uint32_t j = i ^ _hashing->getHash(f);

		auto bucket_i = _table->find(i);
		auto bucket_j = _table->find(j);

		if (bucket_i != _table->end() && 
			std::find(bucket_i->second->begin(), bucket_i->second->end(), f) != bucket_i->second->end()) {
			bucket_i->second->erase(std::remove(bucket_i->second->begin(), bucket_i->second->end(), f), bucket_i->second->end());
			return true;
		}
		else if (bucket_j != _table->end() && 
				 std::find(bucket_j->second->begin(), bucket_j->second->end(), f) != bucket_j->second->end()) {
			bucket_j->second->erase(std::remove(bucket_j->second->begin(), bucket_j->second->end(), f), bucket_j->second->end());
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
		uint32_t i2 = i1 ^ _hashing->getHash(f);

		auto bucket1 = _table->find(i1);
		auto bucket2 = _table->find(i2);

		if (bucket1 == _table->end()) {
			_table->insert(std::pair<uint32_t, std::vector<uint32_t>*>(i1, new std::vector<uint32_t>()));
			bucket1 = _table->find(i1);
		}
		if (bucket2 == _table->end()) {
			_table->insert(std::pair<uint32_t, std::vector<uint32_t>*>(i2, new std::vector<uint32_t>()));
			bucket2 = _table->find(i2);
		}

		if (bucket1->second->size() < _bucketSize){
			bucket1->second->push_back(f);
			return true;
		}
		else if (bucket2->second->size() < _bucketSize){
			bucket2->second->push_back(f);
			return true;
		}

		auto i = rand() % 2 ? i2 : i1;

		for (uint32_t n = 0; n < _maxNumberOfKicks; n++){
			auto bucket = _table->find(i);
			uint32_t randIndex = rand() % bucket->second->size();
			auto temp = bucket->second->at(randIndex);
			bucket->second->at(randIndex) = f;
			f = temp;
			i = i ^ _hashing->getHash(f);
			bucket = _table->find(i);
			if (bucket != _table->end() && bucket->second->size() < _bucketSize){
				bucket->second->push_back(f);
				return true;
			}
		}

		return false;
	}

	uint32_t CuckooFilter::fingerprint(std::string val) {
		return hasher(val);
	}

}