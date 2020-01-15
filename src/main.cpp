#include <iostream>
#include <sstream>
#include <string>

#include "cuckooFilter.hh"
#include "efficientCuckooFilter.hh"
#include "dynamicCuckooFilter.hh"
#include "cuckooHashing.hh"
#include "dataLoader.hh"
#include "testingSuite.hh"


int main(int argc, char *argv[]) {

	if (argc == 2){
		// ------ for generating test files ------
		std::vector<std::pair<uint32_t, uint32_t>> fileGenInfo = {
			std::make_pair(100, 100000), 
			std::make_pair(20, 1000),
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
			std::make_pair(100, 1000000),
		};
		std::cout << "Generating test files" << std::endl;
		generateTestFiles(argv[1], fileGenInfo);
		return 0;
	}

	if (argc != 5) {
		std::cout << "Usage: cuckoo_filter [path_to_genome_file] [kmerlength] [kmernum] [bucketnumber]" << std::endl;
		return 1;
	}
	
	uint32_t bucketSize = 4;
	uint32_t bucketNumber = std::stoi(argv[4]);
	uint32_t fingerprintSize = 16;
	uint32_t maxNumberOfKicks = 500;
	int testKmersCount = 1000;

	cuckoo::CuckooHashing* hashingAlg = new cuckoo::CuckooHashing(bucketNumber);
	cuckoo::Filter* fltrE = new cuckoo::CuckooFilter(bucketSize, bucketNumber, fingerprintSize, maxNumberOfKicks, hashingAlg);
	cuckoo::Filter* fltrD = new cuckoo::DynamicCuckooFilter(bucketSize, bucketNumber, fingerprintSize, maxNumberOfKicks, hashingAlg);

	std::cout << "\n---------- Cuckoo filter ----------" << std::endl;
	benchmarkFilter(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), "dataStatic.csv", fltrE, testKmersCount);

	std::cout << "\n---------- Dynamic Cuckoo filter ----------" << std::endl;
	benchmarkFilter(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), "dataDynamic.csv", fltrD, testKmersCount);
	
	delete fltrE;
	delete fltrD;
	delete hashingAlg;
    return 0;
}
