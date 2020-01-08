#include <iostream>
#include "cuckooFilter.hh"
#include "cuckooHashing.hh"
#include <stdint.h>

int main() {

	uint32_t bucketSize = 4;
	uint32_t fingerprintSize = 8;

	cuckoo::CuckooHashing* hashingAlg = new cuckoo::CuckooHashing();
	cuckoo::CuckooFilter* fltr = new cuckoo::CuckooFilter(bucketSize, fingerprintSize, hashingAlg);

	delete fltr;
    return 0;
}