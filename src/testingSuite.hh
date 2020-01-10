#ifndef TESTING_SUITE_HH
#define TESTING_SUITE_HH

#include <string>
#include <vector>
#include <stdint.h>

std::vector<std::string> generateTestFiles(
    const std::string& fromfile, 
    const std::vector<std::pair<uint32_t,
    uint32_t>>& fileGenInfo
    );


std::vector<std::string>* generateNeKmers(int numberOfKmers, const std::vector<std::string>* kmers);

bool outputStats(
	const std::string filepath,
    int kmerSize,
    int numberOfKmers,
    int timeOfExec,
    uint64_t memoryUsed,
    float fpRate);


bool benchmarkFilter(
		const std::string inputFile,
		const std::string outputFile,
		cuckoo::Filter *fltr,
		int numberOfTestKmers = 1000
		);

#endif // !TESTING_SUITE_HH
