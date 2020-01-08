#include <iostream>
#include <stdint.h>
#include <fstream>
#include <memory>

#include "cuckooFilter.hh"
#include "cuckooHashing.hh"
#include "dataLoader.hh"

int main(int argc, char *argv[]) {

	if (argc < 2) {
		std::cout << "Provide input file" << std::endl;
		return 1;
	}

	std::ifstream file (argv[1], std::ifstream::binary);
	if(!file)
	{
		std::cout << "Error in opening file..!!" << std::endl;
		std::exit(1);
	}
	
	uint32_t bucketSize = 4;
	uint32_t bucketNumber = 500;
	uint32_t fingerprintSize = 8;
	uint32_t maxNumberOfKicks = 500;

	cuckoo::CuckooHashing* hashingAlg = new cuckoo::CuckooHashing(bucketNumber);
	cuckoo::CuckooFilter* fltr = new cuckoo::CuckooFilter(bucketSize, bucketNumber, fingerprintSize, maxNumberOfKicks, hashingAlg);

	uint16_t kSize = 10;
	uint32_t kCount = 10000;
	std::vector<std::string>* kmers = cuckoo::DataLoader::loadFromFile(argv[1], kSize, kCount);

	for (auto it = kmers->begin(); it != kmers->end(); it++) {
		bool success = fltr->insert(*it);
		if (!success) break;
	}

	std::cout << fltr->lookup("GTAAGTATTT") << std::endl;
	std::cout << fltr->lookup("CAGCTTTTCA") << std::endl;
	std::cout << fltr->lookup("CAGCETTTCA") << std::endl;
	
	delete fltr;
    return 0;
}