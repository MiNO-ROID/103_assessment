#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "admin_auth.h"

namespace fs = std::filesystem;
const std::string ADMIN_FILE = "CSV/admin.csv";

namespace adminauth {

    void ensureAdminFile() {
        fs::create_directories("CSV");
        // If file doesn't exist, create it with header
        if (!fs::exists(ADMIN_FILE)) {
            std::ofstream f(ADMIN_FILE);
            f << "username,password\n";
            f << "admin,admin123\n";
        }
    }

    std::vector<std::pair<std::string,std::string>> loadAdmins() {
        ensureAdminFile();
        std::vector<std::pair<std::string,std::string>> admins;
        std::ifstream file(ADMIN_FILE);
        if (!file.is_open()) return admins;

        std::string line;
        std::getline(file, line); // skip header

        while (std::getline(file, line)) {
            if (line.empty()) continue;
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
        for (const auto& a : admins) {
            if (a.first == username) return false;
        }
        std::ofstream file(ADMIN_FILE, std::ios::app);
        file << username << "," << password << "\n";
        return true;
    }
}
