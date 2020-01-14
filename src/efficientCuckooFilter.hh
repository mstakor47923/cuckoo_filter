#ifndef EFFICIENT_CUCKOO_FILTER_HH
#define EFFICIENT_CUCKOO_FILTER_HH

#include <cuckoofilter/cuckoofilter.h>

#include "filter.hh"
#include "cuckooHashing.hh"

namespace cuckoo {
    class EfficientCuckooFilter : public Filter {
	private:
		uint32_t _bucketSize, _bucketNumber, _fingerPrintSize, _maxNumberOfKicks;
        CuckooHashing* _hashing;
		cuckoofilter::CuckooFilter<uint16_t, 16>* _filter;
	public:
		EfficientCuckooFilter(
			uint32_t bucketSize, uint32_t bucketNumber,
			uint32_t fingerPrintSize, uint32_t maxNumberOfKicks,
			CuckooHashing* hashingAlg);
		~EfficientCuckooFilter();

		virtual bool lookup(std::string val);
		virtual bool remove(std::string val);
		virtual bool insert(std::string val);
		virtual uint32_t getCalculatedMemoryUsage();
	private:
		uint32_t fingerprint(std::string val);
	};
}

#endif