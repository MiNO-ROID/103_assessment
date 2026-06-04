#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../Header/admin_auth.h"

const std::string ADMIN_FILE = "../CSV/admin.csv";

namespace adminauth {

    // Load all admins from CSV
    std::vector<std::pair<std::string,std::string>> loadAdmins() {
        std::vector<std::pair<std::string,std::string>> admins;
        std::ifstream file(ADMIN_FILE);
        if (!file.is_open()) return admins;

        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string u, p;
            std::getline(ss, u, ',');
            std::getline(ss, p, ',');
            if (!u.empty()) admins.push_back({u, p});
        }
        return admins;
    }

    bool loginAdmin(const std::string& username, const std::string& password) {
        auto admins = loadAdmins();
        for (const auto& a : admins) {
            if (a.first == username && a.second == password) return true;
        }
        return false;
    }

    bool registerAdmin(const std::string& username, const std::string& password) {
        auto admins = loadAdmins();

        // Check if username exist
        for (const auto& a : admins) {
            if (a.first == username) return false;
        }

        // Append new admin to CSV
        std::ofstream file(ADMIN_FILE, std::ios::app);
        file << username << "," << password << "\n";
        return true;
    }
}
