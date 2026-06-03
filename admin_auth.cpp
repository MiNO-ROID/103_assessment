#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "admin_auth.h"

namespace adminauth {

    bool loginAdmin(const std::string& username, const std::string& password) {
        std::ifstream file("admin.csv");
        if (!file.is_open()) return false;

        std::string line;
        std::getline(file, line); // skip header

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string fileUser, filePass;

            std::getline(ss, fileUser, ',');
            std::getline(ss, filePass, ',');

            if (fileUser == username && filePass == password) {
                return true;
            }
        }
        return false;
    }
}
