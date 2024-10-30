#ifndef STRING_SET
#define STRING_SET

#include <string>
#include <unordered_set>
#include <filesystem>

#include "../libs/logging.h"

namespace prophet {

// A class that can hold a set of strings. The class persists any mutations to storage so that the
// previous state can be restored in the event of crashes.
class StringSet {
    public:
        // `file_path` is the path where the mutations are persisted.
        StringSet(const std::filesystem::path& file_path);

        void Add(const std::string& item);
        void Remove(const std::string& item);
        bool Contains(const std::string& item) const;

        void DebugLog() const;
        
    private:
        std::unordered_set<std::string> data_;
        LogWriter log_writer_;
};

}

#endif