#pragma once
#include <string>

namespace adminauth {
    bool loginAdmin(const std::string& username, const std::string& password);
    bool registerAdmin(const std::string& username, const std::string& password);
}
