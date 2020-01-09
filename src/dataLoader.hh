#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

namespace cuckoo {

    class DataLoader {
    public:
        static std::vector<std::string>* loadFromFile(std::string filePath, uint16_t k, uint32_t kmerCount) {
            std::ifstream file(filePath, std::ifstream::out);
            if (!file) {
                std::cout << "Error in opening file..!!" << std::endl;
                std::exit(1);
            }

            std::string firstLine;
            std::getline(file, firstLine);

            int position = firstLine.length() + 1;

            std::vector<std::string>* kmers = new std::vector<std::string>();

            for (int i = 0; i < kmerCount; i++) {
                file.seekg(position);

                std::string buffer (k + 2, '\0');
                file.read(&buffer[0], k + 2);
                file.seekg(++position);
                
                buffer.erase(std::remove(buffer.begin(), buffer.end(), '\n'), buffer.end());
                std::string kmer = std::string(buffer.substr(0, k));

                if (kmer.length() == k) {
                    kmers->push_back(kmer);
                } else {
                    break;
                }
            }

            file.close();
            kmers->shrink_to_fit();
            return kmers;
        }

        static std::vector<std::string>* loadKmersFromFile(std::string filename) {
            std::ifstream file(filename, std::ifstream::in);
            if (file.is_open()) {
                std::string kmer;
                std::vector<std::string>* kmers = new std::vector<std::string>();
                while(file >> kmer) {
                    kmer.erase(std::remove(kmer.begin(), kmer.end(), '\n'), kmer.end());
                    kmers->push_back(kmer);
                }

                file.close();
                return kmers;
            } else {
                std::cout << "Error in opening file..!!" << std::endl;
                return nullptr;
            }
        }

        static void saveKmersToFile(std::string filepath, const std::vector<std::string>* kmers) {
            std::ofstream file(filepath, std::ofstream::out);
            if (file.is_open()) {
                for (auto it = kmers->begin(); it != kmers->end(); it++) {
                    file << *it << std::endl;
                }

                file.close();
            }
        }
    };
}