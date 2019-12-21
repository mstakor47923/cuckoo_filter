#include <iostream>
#include <vector>
#include <map>
#include "cuckooFilter.hh"

namespace cuckoo {
	
	CuckooFilter::CuckooFilter(uint32_t bucketSize, uint32_t fingerPrintSize, CuckooHashing* hashingAlg)
		: _bucketSize(bucketSize), _fingerPrintSize(fingerPrintSize) {
		_table = new std::map<uint32_t, std::vector<uint32_t>>();
		_hashing = hashingAlg;
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
		return false;
	}

	uint32_t CuckooFilter::fingerprint(uint32_t val)
	{
		return 0;
	}

}