#include <iostream>
#include <sstream>
#include <chrono>

#include "cuckooFilter.hh"
#include "dynamicCuckooFilter.hh"
#include "cuckooHashing.hh"
#include "dataLoader.hh"

std::vector<std::string> generateTestFiles(const std::string& fromfile, const std::vector<std::pair<uint32_t, uint32_t>>& fileGenInfo) {
	std::vector<std::string> filePaths;
	for (auto it = fileGenInfo.begin(); it != fileGenInfo.end(); it++) {
		std::vector<std::string>* kmers = cuckoo::DataLoader::loadFromFile(fromfile, it->first, it->second);
		std::stringstream ss;
		ss << "./" << it->first << "mer-" << it->second << ".txt";
		cuckoo::DataLoader::saveKmersToFile(ss.str(), kmers);

		filePaths.push_back(ss.str());
	}

	return filePaths;
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		std::cout << "Usage: cuckoo_filter [path_to_genome_file]" << std::endl;
		return 1;
	}
	
	// ------ for generating test files ------
	std::vector<std::pair<uint32_t, uint32_t>> fileGenInfo = {
		std::make_pair(100, 10000), 
		std::make_pair(50, 10000)
	};
	generateTestFiles(argv[1], fileGenInfo);

	uint32_t bucketSize = 4;
	uint32_t bucketNumber = 500;
	uint32_t fingerprintSize = 32;
	uint32_t maxNumberOfKicks = 500;

	cuckoo::CuckooHashing* hashingAlg = new cuckoo::CuckooHashing(bucketNumber);
	cuckoo::Filter* fltr = new cuckoo::DynamicCuckooFilter(bucketSize, bucketNumber, fingerprintSize, maxNumberOfKicks, hashingAlg);

	uint16_t kSize = 10;
	uint32_t kCount = 10000;
	auto kmers = cuckoo::DataLoader::loadFromFile(argv[1], kSize, kCount);

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
