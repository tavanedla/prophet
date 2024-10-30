#ifndef IP_RANGES_
#define IP_RANGES_

#include <string>
#include <filesystem>

#include "../libs/logging.h"
#include "trie.h"

namespace prophet {

// A class that can hold multiple IP ranges provided in CIDR format. It can answer if a given IP
// falls in one of ranges previously added.
// The class also persists the mutations to storage, so it can restore previous state in case of 
// task crashes.
class IpRanges {
    public:
        explicit IpRanges(const std::filesystem::path& file_path);

        // Add a range. Can be called multiple times on the same input. 
        void Add(const std::string& ip_cidr);

        // Removes a range if it exists, else does nothing.
        bool Remove(const std::string& ip_cidr);

        // Returns true if the given ip_addr falls in the ranges contained by this object.
        bool Contains(const std::string& ip_addr) const;
    
    private:
        BinaryTrie trie_;
        LogWriter log_writer_;
};

}

#endif