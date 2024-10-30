#ifndef SUSPICIOUS_IPS_
#define SUSPICIOUS_IPS_

#include <string>

#include "../data_structures/ip_ranges.h"
#include "../data_structures/string_set.h"

namespace prophet {

class SuspiciousIps {
    public:
        SuspiciousIps(const std::filesystem::path& data_dir);
        bool Contains(const std::string& ip) const;
        void AddSuspiciousBlock(const std::string& ip_block);
        void RemoveSuspiciousBlock(const std::string& ip_block);
        void AddBadIp(const std::string& ip);
    
    private:
        IpRanges blocked_ranges_;
        StringSet blocked_ips_;
};

}

#endif