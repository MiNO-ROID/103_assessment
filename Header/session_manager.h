#pragma once
#include <string>
#include <vector>

namespace sessions {

    struct ServiceEntry {
        std::string name;
        double ratePerUnit;
        int units;
        double cost;
    };

    struct SessionRecord {
        std::string username;
        std::vector<ServiceEntry> services;
        double totalCost;
        std::string date;
    };

    void startCafeSession(const std::string& username);
    void viewSessionHistory(const std::string& username);
    void saveSession(const SessionRecord& record);
}
