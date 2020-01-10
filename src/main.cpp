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
			std::make_pair(10, 1000), 
			/*std::make_pair(20, 1000),
			std::make_pair(50, 1000),
			std::make_pair(100, 1000),
			std::make_pair(10, 10000), 
			std::make_pair(20, 10000),
			std::make_pair(50, 10000),
			std::make_pair(100, 10000),
			std::make_pair(10, 100000), 
			std::make_pair(20, 100000),
			std::make_pair(50, 100000),
			std::make_pair(100, 100000),
			std::make_pair(10, 1000000), 
			std::make_pair(20, 1000000),
			std::make_pair(50, 1000000),
			std::make_pair(100, 1000000),*/
		};
		generateTestFiles(argv[1], fileGenInfo);
		return 0;
	}
	

	uint32_t bucketSize = 4;
	uint32_t bucketNumber = 500;
	uint32_t fingerprintSize = 11;
	uint32_t maxNumberOfKicks = 5;
	uint32_t numberOfTestKmers = 1000;

	cuckoo::CuckooHashing* hashingAlg = new cuckoo::CuckooHashing(bucketNumber);
	cuckoo::Filter* fltr = new cuckoo::DynamicCuckooFilter(bucketSize, bucketNumber, fingerprintSize, maxNumberOfKicks, hashingAlg);

	auto start = std::chrono::system_clock::now();
	auto kmers = cuckoo::DataLoader::loadKmersFromFile(argv[1]);
	auto end = std::chrono::system_clock::now();
	auto elapsedForLoading = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Loading duration: " << elapsedForLoading.count() << "ms" << std::endl;

	start = std::chrono::system_clock::now();
	auto mutatedKmers = generateNeKmers(numberOfTestKmers, kmers);
	end = std::chrono::system_clock::now();
	auto elapsedForGeneratingNeKmers = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Generate non existing Kmers duration: " << elapsedForGeneratingNeKmers.count() << "ms" << std::endl;

	start = std::chrono::system_clock::now();
	for (auto it = kmers->begin(); it != kmers->end(); it++) {
		bool success = fltr->insert(*it);
		//if (!success) break;
	}
	end = std::chrono::system_clock::now();
	auto elapsedForInsert = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Insert duration: " << elapsedForInsert.count() << "ms" << std::endl;

	int fp(0);
	for (auto it = mutatedKmers->begin(); it != mutatedKmers->end(); ++it){
		if (fltr->lookup(*it)){
			//std::cout << "False positive: " << *it  << std::endl;
			++fp;
		}
	}
	std::cout << "Fp rate: " << (float)fp/numberOfTestKmers << std::endl;
	std::cout << "Memory taken " << (double)(fltr->getCalculatedMemoryUsage() / 1024) << " kB" << std::endl;

	outputStats("data.csv", 10, 100, elapsedForInsert.count(), -1, fpRate);

	delete fltr;
	delete hashingAlg;
	delete kmers;
    return 0;
}
