#ifndef SUSPICIOUS_EVENTS_READER_
#define SUSPICIOUS_EVENTS_READER_

#include <iostream>
#include <string>
#include <vector>

#include "libs/logging.h"

namespace prophet {

class SuspiciousEventsReader {
    public:
        SuspiciousEventsReader(const std::filesystem::path& filepath) : reader_(filepath) {}
        
        std::vector<std::string> Read(int n) {
            std::vector<std::string> results;
            reader_.Start();
            std::string line;
            while (reader_.Next(line) && n--) {
                results.emplace_back(line);
            }
            reader_.Close();
            return results;
        }

    private:
        LogReader reader_;
};

}

#endif