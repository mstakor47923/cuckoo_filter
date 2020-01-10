#include <iostream>
#include <sstream>
#include <chrono>

#include "cuckooFilter.hh"
#include "dynamicCuckooFilter.hh"
#include "cuckooHashing.hh"
#include "dataLoader.hh"
#include "testingSuite.hh"


int main(int argc, char *argv[]) {

	if (argc < 2) {
		std::cout << "Usage: cuckoo_filter [path_to_genome_file]" << std::endl;
		return 1;
	};

	// ------ for generating test files ------
	std::vector<std::pair<uint32_t, uint32_t>> fileGenInfo = {
	std::make_pair(100, 10000), 
	std::make_pair(50, 10000)
	};
	//generateTestFiles(argv[1], fileGenInfo);
	

	uint32_t bucketSize = 4;
	uint32_t bucketNumber = 500;
	uint32_t fingerprintSize = 32;
	uint32_t maxNumberOfKicks = 500;

	cuckoo::CuckooHashing* hashingAlg = new cuckoo::CuckooHashing(bucketNumber);
	cuckoo::Filter* fltr = new cuckoo::DynamicCuckooFilter(bucketSize, bucketNumber, fingerprintSize, maxNumberOfKicks, hashingAlg);

	uint16_t kSize = 100;
	uint32_t kCount = 10000;
	auto kmers = cuckoo::DataLoader::loadFromFile(argv[1], kSize, kCount);
	auto mutatedKmers = generateNeKmers(1000, kmers);
	for (auto it = mutatedKmers->begin(); it != mutatedKmers->end(); ++it){
		std::cout << (*it) << std::endl;
	}

	auto start = std::chrono::system_clock::now();
	for (auto it = kmers->begin(); it != kmers->end(); it++) {
		bool success = fltr->insert(*it);
		if (!success) break;
	}
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Insert duration: " << elapsed.count() << "ms" << std::endl;

	delete fltr;
	delete hashingAlg;
	delete kmers;
    return 0;
}
