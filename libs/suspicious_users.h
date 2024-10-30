#ifndef SUSPICIOUS_USERS_
#define SUSPICIOUS_USERS_

#include <string>

#include "../data_structures/string_set.h"

namespace prophet {

class SuspiciousUsers {
    public:
        explicit SuspiciousUsers(const std::filesystem::path& data_dir);
        void Add(const std::string& user);
        void Remove(const std::string& user);
        bool Contains(const std::string& user) const;

    private:
        StringSet users_;
};

}

#endif