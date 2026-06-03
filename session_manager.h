#pragma once
#include <string>
#include <vector>

namespace sessions {

    struct SessionRecord {
        std::string username;
        int minutes;
        double cost;
        std::string date;
    };

    const double RATE_PER_MINUTE = 0.05;

    void endSession(const std::string& username);
    void viewSessionHistory(const std::string& username);
    void saveSession(const SessionRecord& record);
    std::vector<SessionRecord> loadSessions(const std::string& username);
}
