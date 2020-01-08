#include "cuckooHashing.hh"

namespace cuckoo {
	
	CuckooHashing::CuckooHashing(int maxHashNum): _maxHashNum(maxHashNum)
	{
	}

	uint32_t CuckooHashing::getHash(const std::string& val)
	{
		return val.length() * 50 % _maxHashNum;
	}

	uint32_t CuckooHashing::getHash(const uint32_t val)
	{
		return val * 50 % _maxHashNum;
	}
}