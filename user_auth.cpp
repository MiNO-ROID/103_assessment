#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "user_auth.h"

const std::string USER_FILE = "users.csv";

namespace auth {

    std::vector<User> loadUsers() {
        std::vector<User> users;
        std::ifstream file(USER_FILE);
        std::string line;

        std::getline(file, line); // skip header

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string username, password, balanceStr;

            std::getline(ss, username, ',');
            std::getline(ss, password, ',');
            std::getline(ss, balanceStr, ',');

            if (!username.empty()) {
                users.push_back({username, password, std::stod(balanceStr)});
            }
        }
        return users;
    }

    void saveUsers(const std::vector<User>& users) {
        std::ofstream file(USER_FILE);
        file << "username,password,balance\n";
        for (const auto& u : users) {
            file << u.username << "," << u.password << "," << u.balance << "\n";
        }
    }

    bool registerUser(const std::string& username, const std::string& password) {
        std::vector<User> users = loadUsers();

        for (const auto& u : users) {
            if (u.username == username) {
                return false;
            }
        }

        users.push_back({username, password, 0.00});
        saveUsers(users);
        return true;
    }

    bool loginUser(const std::string& username, const std::string& password, User& outUser) {
        std::vector<User> users = loadUsers();

        for (const auto& u : users) {
            if (u.username == username && u.password == password) {
                outUser = u;
                return true;
            }
        }
        return false;
    }
}
