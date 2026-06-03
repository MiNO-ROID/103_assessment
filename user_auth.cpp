#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "user_auth.h"

using namespace std;

const string USER_FILE = "users.csv";

namespace auth {
    //load user
    vector<User> loadUsers() {
        vector<User> users;
        ifstream file(USER_FILE);
        string line;

        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string username, password, balanceStr;

            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, balanceStr, ',');

            if (!username.empty()) {
                users.push_back({username, password, stod(balanceStr)});
            }
        }
        return users;
    }

    // Save user to csv
    void saveUsers(const vector<User> &users) {
        ofstream file(USER_FILE);
        file << "username,password,balance\n";
        for (const auto &u: users) {
            file << u.username << "," << u.password << "," << u.balance << "\n";
        }
    }

    // new user fail if username is taken
    bool registerUser(const std::string &username, const std::string &password) {
        std::vector<User> users = loadUsers();

        for (const auto &u: users) {
            if (u.username == username) {
                return false; // username already exists
            }
        }

        users.push_back({username, password, 0.00});
        saveUsers(users);
        return true;
    }

    // fail login
    bool loginUser(const std::string &username, const std::string &password, User &outUser) {
        std::vector<User> users = loadUsers();

        for (const auto &u: users) {
            if (u.username == username && u.password == password) {
                outUser = u;
                return true;
            }
        }
        return false;
    }
}
