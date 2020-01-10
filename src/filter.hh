#include <string>

namespace cuckoo {
    class Filter {
        public:
            virtual bool lookup(std::string val) = 0;
            virtual bool remove(std::string val) = 0;
            virtual bool insert(std::string val) = 0;
    };
}