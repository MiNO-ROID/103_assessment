#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include "../Header/session_manager.h"
#include "../Header/termcolor.hpp"

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

    std::string formatMoney(double amount) {
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << amount;
        return "$" + ss.str();
    }

    void saveSession(const SessionRecord& record) {
        std::ifstream check(SESSION_FILE);
        bool isEmpty = check.peek() == std::ifstream::traits_type::eof();
        check.close();

        std::ofstream file(SESSION_FILE, std::ios::app);
        if (isEmpty) file << "username,date,totalCost,services\n";

        file << record.username << ","
             << record.date << ","
             << std::fixed << std::setprecision(2) << record.totalCost << ",";

        for (size_t i = 0; i < record.services.size(); ++i) {
            const auto& s = record.services[i];
            file << s.name << "|" << s.units << "|"
                 << std::fixed << std::setprecision(2) << s.cost;
            if (i + 1 < record.services.size()) file << ";";
        }
        file << "\n";
    }

    void startCafeSession(const std::string& username) {
        // Internet & Gaming: per minute | Print & Scan: per item
        std::vector<ServiceEntry> services = {
            {"Internet Browsing", 0.03, 0, 0.0},
            {"Gaming",            0.08, 0, 0.0},
            {"Print",             0.12, 0, 0.0},
            {"Scan",              0.10, 0, 0.0}
        };

        int choice = 0;
        std::vector<ServiceEntry> usedServices;
        double total = 0.0;

        do {
            std::cout << "\n" << termcolor::cyan;
            printCenteredSM("======== CAFE SERVICES ========");
            std::cout << termcolor::yellow;
            printCenteredSM("1. Internet Browsing  - $0.03/min");
            printCenteredSM("2. Gaming             - $0.08/min");
            printCenteredSM("3. Print              - $0.12/page");
            printCenteredSM("4. Scan               - $0.10/page");
            printCenteredSM("5. Finish & View Summary");
            std::cout << termcolor::reset;
            std::cout << std::string((CONSOLE_WIDTH - 18) / 2, ' ') << "Choose service: ";
            std::cin >> choice;

            if (choice >= 1 && choice <= 4) {
                ServiceEntry& picked = services[choice - 1];
                int units;

                bool isPrintScan = (choice == 3 || choice == 4);
                std::string unitLabel = isPrintScan ? "pages" : "minutes";

                std::cout << std::string((CONSOLE_WIDTH - 10) / 2, ' ')
                          << "How many " << unitLabel << " for " << picked.name << ": ";
                std::cin >> units;

                if (units > 0) {
                    double cost = picked.ratePerUnit * units;
                    usedServices.push_back({picked.name, picked.ratePerUnit, units, cost});
                    total += cost;
                    std::cout << termcolor::green;
                    printCenteredSM("Added: " + picked.name + " - " + std::to_string(units) + " " + unitLabel + " - " + formatMoney(cost));
                    std::cout << termcolor::reset;
                } else {
                    std::cout << termcolor::red;
                    printCenteredSM("Invalid input. Not added.");
                    std::cout << termcolor::reset;
                }

            } else if (choice != 5) {
                std::cout << termcolor::red;
                printCenteredSM("Invalid choice.");
                std::cout << termcolor::reset;
            }

        } while (choice != 5);

        if (usedServices.empty()) {
            std::cout << termcolor::yellow;
            printCenteredSM("No services used. Session cancelled.");
            std::cout << termcolor::reset;
            return;
        }

        SessionRecord record{username, usedServices, total, getCurrentDate()};
        saveSession(record);

        std::cout << "\n" << termcolor::cyan;
        printCenteredSM("======== SESSION SUMMARY ========");
        std::cout << termcolor::yellow;
        for (const auto& s : usedServices) {
            bool isPrintScan = (s.name == "Print" || s.name == "Scan");
            std::string unitLabel = isPrintScan ? "pages" : "mins";
            std::ostringstream line;
            line << s.name << " | " << s.units << " " << unitLabel << " | " << formatMoney(s.cost);
            printCenteredSM(line.str());
        }
        printCenteredSM("---------------------------------");
        std::cout << termcolor::green;
        printCenteredSM("TOTAL: " + formatMoney(total));
        std::cout << termcolor::reset;
    }

    void viewSessionHistory(const std::string& username) {
        std::ifstream file(SESSION_FILE);
        std::string line;
        std::getline(file, line);

        std::cout << "\n" << termcolor::cyan;
        printCenteredSM("======== SESSION HISTORY ========");
        std::cout << termcolor::reset;

        bool found = false;
        double grandTotal = 0.0;
        int sessionNum = 1;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string uname, date, totalCost, servicesStr;
            std::getline(ss, uname, ',');
            std::getline(ss, date, ',');
            std::getline(ss, totalCost, ',');
            std::getline(ss, servicesStr);

            if (uname == username) {
                found = true;
                std::cout << termcolor::yellow;
                printCenteredSM("--- Session " + std::to_string(sessionNum++) + " | " + date + " ---");

                std::stringstream sv(servicesStr);
                std::string entry;
                while (std::getline(sv, entry, ';')) {
                    std::stringstream se(entry);
                    std::string name, units, cost;
                    std::getline(se, name, '|');
                    std::getline(se, units, '|');
                    std::getline(se, cost, '|');
                    bool isPrintScan = (name == "Print" || name == "Scan");
                    std::string unitLabel = isPrintScan ? "pages" : "mins";
                    printCenteredSM(name + " | " + units + " " + unitLabel + " | $" + cost);
                }

                printCenteredSM("Total: $" + totalCost);
                printCenteredSM("---------------------------------");
                grandTotal += std::stod(totalCost);
            }
        }

        if (!found) {
            std::cout << termcolor::yellow;
            printCenteredSM("No session history found.");
        } else {
            std::cout << termcolor::green;
            std::ostringstream gt;
            gt << std::fixed << std::setprecision(2) << grandTotal;
            printCenteredSM("All-time Total Spent: $" + gt.str());
        }
        std::cout << termcolor::reset;
    }
}
