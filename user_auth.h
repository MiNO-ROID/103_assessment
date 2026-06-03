#pragma once
#include <string>
#include <vector>

namespace auth {
    struct User {
        std::string username;
        std::string password;
        double balance;
    };

    std::vector<User> loadUsers();
    void saveUsers(const std::vector<User>& users);
    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password, User& outUser);
}
