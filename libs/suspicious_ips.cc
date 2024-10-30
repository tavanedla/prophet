#include "suspicious_ips.h"

namespace prophet {

constexpr std::string_view BLOCKED_CIDR_LOG_FILE = "blocked_cidr.txt";
constexpr std::string_view BLOCKED_IPS_LOG_FILE = "blocked_ips.txt";

SuspiciousIps::SuspiciousIps(const std::filesystem::path& data_dir) : 
        blocked_ranges_(data_dir / BLOCKED_CIDR_LOG_FILE),
        blocked_ips_(data_dir / BLOCKED_IPS_LOG_FILE) {}

bool SuspiciousIps::Contains(const std::string& ip) const {
    return blocked_ranges_.Contains(ip) || blocked_ips_.Contains(ip);
}

void SuspiciousIps::AddSuspiciousBlock(const std::string& ip_block) {
    blocked_ranges_.Add(ip_block);
}

void SuspiciousIps::RemoveSuspiciousBlock(const std::string& ip_block) {
    blocked_ranges_.Remove(ip_block);
}

void SuspiciousIps::AddBadIp(const std::string& ip) {
    blocked_ips_.Add(ip);
}


}