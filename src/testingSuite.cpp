
//#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <algorithm>
#include "dataLoader.hh"
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "filter.hh"

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

bool outputStats(
	const std::string filepath,
	int kmerSize,
	int numberOfKmers,
	int timeOfExec,
	uint64_t memoryUsed,
	float fpRate){
		std::ofstream file(filepath, std::ofstream::app);
		if (file.is_open()) {
			file << std::to_string(kmerSize) << ','
				 << std::to_string(numberOfKmers) << ','
				 << std::to_string(timeOfExec) << ','
				 << std::to_string(memoryUsed) << ','
				 << std::to_string(fpRate*100)
				 << std::endl;
			file.close();
		}
	return true;
}

bool benchmarkFilter(
		const std::string inputFile,
		int kmerLength,
		int kmerNum,
		const std::string outputFile,
		cuckoo::Filter *fltr,
		int numberOfTestKmers = 1000
		){
	auto start = std::chrono::system_clock::now();
	auto kmers = cuckoo::DataLoader::loadKmersFromFile(inputFile);
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

	outputStats(
		outputFile,
		kmerLength,
		kmerNum,
		elapsedForInsert.count(),
		fltr->getCalculatedMemoryUsage(),
		(float)fp/numberOfTestKmers);
		
	//todo: for which averages out these numbers before outputing

	delete kmers;

	return true;
}