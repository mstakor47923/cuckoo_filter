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

	if (argc > 2){
		// ------ for generating test files ------
		std::vector<std::pair<uint32_t, uint32_t>> fileGenInfo = {
		std::make_pair(100, 1000), 
		std::make_pair(50, 1000)
		};
		generateTestFiles(argv[1], fileGenInfo);
		return 0;
	}
	

	uint32_t bucketSize = 4;
	uint32_t bucketNumber = 2500;
	uint32_t fingerprintSize = 11;
	uint32_t maxNumberOfKicks = 5;
	uint32_t numberOfTestKmers = 100000;


	cuckoo::CuckooHashing* hashingAlg = new cuckoo::CuckooHashing(bucketNumber);
	cuckoo::Filter* fltr = new cuckoo::DynamicCuckooFilter(bucketSize, bucketNumber, fingerprintSize, maxNumberOfKicks, hashingAlg);

	uint16_t kSize = 100;
	uint32_t kCount = 10000;
	auto kmers = cuckoo::DataLoader::loadKmersFromFile(argv[1]);
	auto mutatedKmers = generateNeKmers(numberOfTestKmers, kmers);


	auto start = std::chrono::system_clock::now();
	for (auto it = kmers->begin(); it != kmers->end(); it++) {
		bool success = fltr->insert(*it);
		//if (!success) break;
	}
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Insert duration: " << elapsed.count() << "ms" << std::endl;
	int fp(0);
	for (auto it = mutatedKmers->begin(); it != mutatedKmers->end(); ++it){
		if (fltr->lookup(*it)){
			//std::cout << "False positive: " << *it  << std::endl;
			++fp;
		}
		
	}
	std::cout << "Fp rate: " << (float)fp/numberOfTestKmers << std::endl;
	std::cout << "Memory taken " << bucketNumber*(sizeof(uint32_t)+bucketSize*sizeof(uint32_t)) << std::endl;

	delete fltr;
	delete hashingAlg;
	delete kmers;
    return 0;
}
