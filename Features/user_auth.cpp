#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <random>
#include "../Header/user_auth.h"

const std::string USER_FILE = "../CSV/users.csv";

namespace auth {

    std::vector<User> loadUsers() {
        std::vector<User> users;
        std::ifstream file(USER_FILE);
        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, username, password, balanceStr;
            std::getline(ss, id, ',');
            std::getline(ss, username, ',');
            std::getline(ss, password, ',');
            std::getline(ss, balanceStr, ',');
            if (!username.empty()) {
                double bal = 0.0;
                try { bal = std::stod(balanceStr); } catch (...) {}
                users.push_back({id, username, password, bal});
            }
        }
        return users;
    }

    void saveUsers(const std::vector<User>& users) {
        std::ofstream file(USER_FILE);
        file << "id,username,password,balance\n";
        for (const auto& u : users) {
            file << u.id << "," << u.username << "," << u.password << ","
                 << std::fixed << std::setprecision(2) << u.balance << "\n";
        }
    }

    // Generate random 8-digit USR- ID, guaranteed unique
    std::string generateId(const std::vector<User>& users) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(10000000, 99999999);

        std::string newId;
        bool unique = false;
        while (!unique) {
            newId = "USR-" + std::to_string(dist(gen));
            unique = true;
            for (const auto& u : users) {
                if (u.id == newId) { unique = false; break; }
            }
        }
        return newId;
    }

    // Pass Val
    PasswordValidation validatePassword(const std::string& password) {
        if (password.length() < 8)
            return {false, "Password must be at least 8 characters."};

        bool hasUpper = false, hasDigit = false, hasSpecial = false;
        const std::string specialChars = "!@#$%^&*()_+-=[]{}|;':,./<>?";

        for (char c : password) {
            if (std::isupper(c))  hasUpper   = true;
            if (std::isdigit(c))  hasDigit   = true;
            if (specialChars.find(c) != std::string::npos) hasSpecial = true;
        }

        if (!hasUpper)   return {false, "Password must contain at least 1 uppercase letter."};
        if (!hasDigit)   return {false, "Password must contain at least 1 number."};
        if (!hasSpecial) return {false, "Password must contain at least 1 special character (!@#$% etc)."};

        return {true, ""};
    }

    bool registerUser(const std::string& username, const std::string& password, std::string& outId) {
        std::vector<User> users = loadUsers();

        for (const auto& u : users) {
            if (u.username == username) return false;
        }

        std::string newId = generateId(users);
        users.push_back({newId, username, password, 0.00});
        saveUsers(users);
        outId = newId;
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
