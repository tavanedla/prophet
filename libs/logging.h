#ifndef LOGGING_H_
#define LOGGING_H_

#include <filesystem>
#include <iostream>
#include <fstream>

namespace prophet {

class LogWriter {
    public:
        LogWriter(const std::filesystem::path& filepath) {
            log_.open(filepath, std::ios_base::app);
        }

        void Append(const std::string& line) {
            log_ << line << std::endl;
            log_.flush();
        }

        ~LogWriter() {
            log_.close();
        }

    private:
        std::ofstream log_;
};

class LogReader {
public:
    LogReader(const std::filesystem::path& filepath) : filepath_(filepath) {
    }

    void Start() {
        log_.open(filepath_);
    }

    bool Next(std::string& line) {
        if (!log_) {
            return false;
        }
        if (log_.peek() == std::ifstream::traits_type::eof()) {
            return false;
        }
        
        char buffer[100];
        log_.getline(buffer, 100);
        for (char c : buffer) {
            if (c == 0) {
                break;
            }
            line.push_back(c);
        }
        return true;
    }

    void Close() {
        log_.close();
    }

private:
    std::ifstream log_;
    std::string filepath_;
};

}

#endif