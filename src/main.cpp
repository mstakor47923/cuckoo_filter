#include <iostream>
#include <sstream>

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

	cuckoo::CuckooHashing* hashingAlg = new cuckoo::CuckooHashing(bucketNumber);
	cuckoo::Filter* fltr = new cuckoo::DynamicCuckooFilter(bucketSize, bucketNumber, fingerprintSize, maxNumberOfKicks, hashingAlg);

	benchmarkFilter(argv[1], "data.csv", fltr);
	
	delete fltr;
	delete hashingAlg;
    return 0;
}
