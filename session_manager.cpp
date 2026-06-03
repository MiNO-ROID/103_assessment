#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include "session_manager.h"
#include "termcolor.hpp"

const std::string SESSION_FILE = "sessions.csv";
const int CONSOLE_WIDTH = 80;

namespace sessions {

    void printCenteredSM(const std::string& text) {
        int padding = (CONSOLE_WIDTH - static_cast<int>(text.length())) / 2;
        if (padding < 0) padding = 0;
        std::cout << std::string(padding, ' ') << text << "\n";
    }

    std::string getCurrentDate() {
        time_t now = time(nullptr);
        char buf[20];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", localtime(&now));
        return std::string(buf);
    }

    void saveSession(const SessionRecord& record) {
        // Check if file empty to write header
        std::ifstream check(SESSION_FILE);
        bool isEmpty = check.peek() == std::ifstream::traits_type::eof();
        check.close();

        std::ofstream file(SESSION_FILE, std::ios::app);
        if (isEmpty) {
            file << "username,minutes,cost,date\n";
        }
        file << record.username << ","
             << record.minutes << ","
             << record.cost << ","
             << record.date << "\n";
    }

    std::vector<SessionRecord> loadSessions(const std::string& username) {
        std::vector<SessionRecord> records;
        std::ifstream file(SESSION_FILE);
        std::string line;

        std::getline(file, line); // skip header

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string uname, minsStr, costStr, date;

            std::getline(ss, uname, ',');
            std::getline(ss, minsStr, ',');
            std::getline(ss, costStr, ',');
            std::getline(ss, date, ',');

            if (uname == username) {
                records.push_back({uname, std::stoi(minsStr), std::stod(costStr), date});
            }
        }
        return records;
    }

    void endSession(const std::string& username) {
        int minutes;

        std::cout << "\n" << termcolor::cyan;
        printCenteredSM("===== END SESSION =====");
        std::cout << termcolor::reset << "\n";

        int pad = (CONSOLE_WIDTH - 10) / 2;
        std::cout << std::string(pad, ' ') << "Minutes: ";
        std::cin >> minutes;

        if (minutes <= 0) {
            std::cout << termcolor::red;
            printCenteredSM("Invalid minutes entered.");
            std::cout << termcolor::reset << "\n";
            return;
        }

        double cost = minutes * RATE_PER_MINUTE;

        SessionRecord record = {username, minutes, cost, getCurrentDate()};
        saveSession(record);

        std::cout << "\n" << termcolor::green;
        printCenteredSM("=====================================");
        printCenteredSM("         SESSION SUMMARY             ");
        printCenteredSM("=====================================");
        printCenteredSM("User     : " + username);
        printCenteredSM("Duration : " + std::to_string(minutes) + " minutes");
        printCenteredSM("Rate     : $0.05 per minute");
        printCenteredSM("Total    : $" + std::to_string(cost));
        printCenteredSM("=====================================");
        std::cout << termcolor::reset << "\n";
    }

    void viewSessionHistory(const std::string& username) {
        std::vector<SessionRecord> records = loadSessions(username);

        std::cout << "\n" << termcolor::cyan;
        printCenteredSM("===== SESSION HISTORY =====");
        std::cout << termcolor::reset << "\n";

        if (records.empty()) {
            std::cout << termcolor::yellow;
            printCenteredSM("No session history found.");
            std::cout << termcolor::reset << "\n";
            return;
        }

        double totalSpent = 0.0;
        int i = 1;
        for (const auto& r : records) {
            std::cout << termcolor::yellow;
            printCenteredSM("--- Session " + std::to_string(i++) + " ---");
            printCenteredSM("Date     : " + r.date);
            printCenteredSM("Duration : " + std::to_string(r.minutes) + " mins");
            printCenteredSM("Cost     : $" + std::to_string(r.cost));
            totalSpent += r.cost;
        }

        std::cout << termcolor::cyan;
        printCenteredSM("=====================================");
        printCenteredSM("Total Spent: $" + std::to_string(totalSpent));
        printCenteredSM("=====================================");
        std::cout << termcolor::reset << "\n";
    }
}
