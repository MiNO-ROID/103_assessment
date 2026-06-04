#pragma once
#include <string>
#include <vector>

namespace auth {

    struct PasswordValidation {
        bool valid;
        std::string error;
    };

    struct User {
        std::string id;
        std::string username;
        std::string password;
        double balance;
    };

    std::vector<User> loadUsers();
    void saveUsers(const std::vector<User>& users);
    PasswordValidation validatePassword(const std::string& password);
    bool registerUser(const std::string& username, const std::string& password, std::string& outId);
    bool loginUser(const std::string& username, const std::string& password, User& outUser);
}
