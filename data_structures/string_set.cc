#include "string_set.h"

#include <iostream>
#include <string_view>

namespace prophet {

namespace {

bool isRemoveLine(const std::string& line) {
    if (line[0] == '0') {
        return true;
    }
    return false;
}

std::string getUserFromLine(const std::string& line) {
    return line.substr(2);
}

std::string createAddLog(const std::string& user) {
    std::string log_line;
    log_line.append("1,");
    log_line.append(user);
    return log_line;
}

std::string createRemoveLog(const std::string& user) {
    std::string log_line;
    log_line.append("0,");
    log_line.append(user);
    return log_line;

}

} // namespace

StringSet::StringSet(const std::filesystem::path& file_path) : log_writer_(file_path) {
    LogReader lr(file_path);
    lr.Start();
    std::string line;
    while (lr.Next(line)) {
        if (isRemoveLine(line)) {
            data_.erase(getUserFromLine(line));
        } else {
            data_.insert(getUserFromLine(line));
        }
        line.clear();
    }
    lr.Close();
}

void StringSet::Add(const std::string& item) {
    log_writer_.Append(createAddLog(item));
    data_.insert(item);
}

void StringSet::Remove(const std::string& item) {
    log_writer_.Append(createRemoveLog(item));
    data_.erase(item);
}

bool StringSet::Contains(const std::string& item) const {
    return data_.contains(item);
}

void StringSet::DebugLog() const {
    std::cout << "StringSet : \n";
    for (auto u : data_) {
        std::cout << u << std::endl;
    }
}

}