
//#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <algorithm>
#include "dataLoader.hh"
#include <stdlib.h>
#include <time.h>

std::vector<std::string> generateTestFiles(const std::string& fromfile, const std::vector<std::pair<uint32_t, uint32_t>>& fileGenInfo) {
	std::vector<std::string> filePaths;
	for (auto it = fileGenInfo.begin(); it != fileGenInfo.end(); it++) {
		std::vector<std::string>* kmers = cuckoo::DataLoader::loadFromFile(fromfile, it->first, it->second);
		std::stringstream ss;
		ss << "./" << it->first << "mer-" << it->second << ".txt";
		cuckoo::DataLoader::saveKmersToFile(ss.str(), kmers);

		filePaths.push_back(ss.str());
        std::cout << "End with" << ss.str() << std::endl;
	}

	return filePaths;
}

std::vector<std::string>* generateNeKmers(int numberOfKmers, const std::vector<std::string>* kmers){
    srand(time(NULL));
    std::vector<std::string>* mutatedKmers = new std::vector<std::string>;
    for (int i = 0; i < numberOfKmers;){
        int kmerIndex = random() % kmers->size();
        std::string mutatedKmer = std::string(kmers->at(kmerIndex));
        int charIndex = random() % mutatedKmer.size();
        char existingChar = mutatedKmer.at(charIndex);
        switch (existingChar)
        {
        case 'A':
            mutatedKmer.at(charIndex) = random() % 3 ? (random() % 2 ? 'G' : 'C') : 'T';
            break;
        case 'T':
            mutatedKmer.at(charIndex) = random() % 3 ? (random() % 2 ? 'A' : 'G') : 'C';
            break;
        case 'C':
            mutatedKmer.at(charIndex) = random() % 3 ? (random() % 2 ? 'T' : 'A') : 'G';
            break;
        case 'G':
            mutatedKmer.at(charIndex) = random() % 3 ? (random() % 2 ? 'C' : 'T') : 'A';
            break;
        default:
            break;
        }
        if(std::find(kmers->begin(), kmers->end(), mutatedKmer) != kmers->end()) {
            continue;
        } else {
            mutatedKmers->push_back(mutatedKmer);
            ++i;
        }
    }
    return mutatedKmers;
}
