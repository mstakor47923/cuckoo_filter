#include <iostream>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <utility>
#include <memory>

#include "cuckooFilter.hh"
#include "cuckooHashing.hh"
#include "dataLoader.hh"

std::vector<std::string> generateTestFiles(const std::string& fromfile, const std::vector<std::pair<uint32_t, uint32_t>>& fileGenInfo) {
	std::vector<std::string> filePaths;
	for (auto it = fileGenInfo.begin(); it != fileGenInfo.end(); it++) {
		std::vector<std::string>* kmers = cuckoo::DataLoader::loadFromFile(fromfile, it->first, it->second);
		std::stringstream ss;
		ss << "/mnt/c/Users/mateo/Desktop/cuckoo-filter/" << it->first << "mer-" << it->second << ".txt";
		cuckoo::DataLoader::saveKmersToFile(ss.str(), kmers);

		filePaths.push_back(ss.str());
	}

	return filePaths;
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		std::cout << "Provide input file" << std::endl;
		return 1;
	}
	
	// ------ for generating test files ------
	// std::vector<std::pair<uint32_t, uint32_t>> fileGenInfo = {
	// 	std::make_pair(100, 10000), 
	// 	std::make_pair(50, 10000)
	// };
	// generateTestFiles(argv[1], fileGenInfo);

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
	
	delete fltr;
    return 0;
}
