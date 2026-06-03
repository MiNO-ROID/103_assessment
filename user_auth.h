#pragma once
#include <string>

namespace auth {
    struct User {
        std::string username;
        std::string password;
        double balance;
    };

    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password, User& outUser);
}
