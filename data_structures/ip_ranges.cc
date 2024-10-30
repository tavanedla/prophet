#include "ip_ranges.h"

#include <bitset>
#include <cassert>
#include <vector>

namespace prophet {

namespace {

int toDigit(char c) {
    assert(c >= '0' && c <= '9');
    return c - '0';
}

uint strToInt(std::string_view str) {
    uint n = 0;
    for (char c : str) {
        n = n * 10 + toDigit(c);
    }
    return n;
}

std::vector<std::string_view> split(std::string_view str, char sep) {
    std::vector<std::string_view> splits;
    size_t start = 0;
    size_t end = 0;
    while (end < str.size()) {
        if (str[end] == sep) {
            splits.push_back(str.substr(start, end - start));
            start = end + 1;
        }
        end++;
    }
    if (start < str.size()) {
        splits.push_back(str.substr(start, end - start));
    }
    return splits;
} 

std::string ipStrToBinaryStr(std::string_view ip_addr) {
    auto addr_splits = split(ip_addr, '.');
    assert(addr_splits.size() == 4);

    uint n = 0;
    for (auto s : addr_splits) {
        n = n << 8; 
        n += strToInt(s);
    }
    std::bitset<32> bits(n);
    return bits.to_string();
}

std::string parseCidrStr(const std::string& cidr_block) {
    auto splits = split(cidr_block, '/');
    assert(splits.size() == 2);
    uint len = strToInt(splits[1]);
    assert(len >= 0 && len <=32);

    auto binary_ip = ipStrToBinaryStr(splits[0]);
    return binary_ip.substr(0, len);
}

std::string createAddLog(const std::string& ip_block) {
    return "1," + ip_block;
}

std::string createEraseLog(const std::string& ip_block) {
    return "0," + ip_block;
}

bool isRemoveLine(const std::string& line) {
    if (line[0] == '0') {
        return true;
    }
    return false;
}

std::string getIpRangeFromLine(const std::string& line) {
    return line.substr(2);
}

} // namespace

IpRanges::IpRanges(const std::filesystem::path& file_path) : log_writer_(file_path) {
    LogReader lr(file_path);
    lr.Start();
    std::string line;
    std::cout << "reading ip ranges \n";
    while (lr.Next(line)) {
        std::cout << "read line : " << line << std::endl;
        if (isRemoveLine(line)) {
            auto binary_ip = parseCidrStr(getIpRangeFromLine(line));
            trie_.Erase(binary_ip);    
        } else {
            std::cout << "Inserting range\n";
            auto binary_ip = parseCidrStr(getIpRangeFromLine(line));
            trie_.Insert(binary_ip);
        }
        line.clear();
    }
    lr.Close();
}

void IpRanges::Add(const std::string& ip_cidr) {
    log_writer_.Append(createAddLog(ip_cidr));
    auto binary_ip = parseCidrStr(ip_cidr);
    trie_.Insert(binary_ip);
}

bool IpRanges::Remove(const std::string& ip_cidr) {
    log_writer_.Append(createEraseLog(ip_cidr));
    auto binary_ip = parseCidrStr(ip_cidr);
    return trie_.Erase(binary_ip);    
}

bool IpRanges::Contains(const std::string& ip) const {
    auto binary_string = ipStrToBinaryStr(ip);
    return trie_.HasPrefix(binary_string);
}

}