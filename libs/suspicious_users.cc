#include "suspicious_users.h"

#include <filesystem>
#include <string_view>

namespace prophet {

constexpr std::string_view SUSPICIOUS_USERS_DATA_FILE = "suspicious_users.txt";

SuspiciousUsers::SuspiciousUsers(const std::filesystem::path& data_dir) 
    : users_(data_dir / SUSPICIOUS_USERS_DATA_FILE) {}

void SuspiciousUsers::Add(const std::string& user) {
    users_.Add(user);
}

void SuspiciousUsers::Remove(const std::string& user) {
    users_.Remove(user);
}

bool SuspiciousUsers::Contains(const std::string& user) const {
    return users_.Contains(user);
}

}