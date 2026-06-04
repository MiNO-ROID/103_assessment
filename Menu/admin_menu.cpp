#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include "../Header/admin_menu.h"
#include "../Header/admin_auth.h"
#include "../Header/user_auth.h"
#include "../Header/termcolor.hpp"

const std::string SESSION_FILE_ADMIN = "sessions.csv";
const int ADMIN_CONSOLE_WIDTH = 80;

namespace adminmenu {

    void printCenteredA(const std::string& text) {
        int padding = (ADMIN_CONSOLE_WIDTH - static_cast<int>(text.length())) / 2;
        if (padding < 0) padding = 0;
        std::cout << std::string(padding, ' ') << text << "\n";
    }

    std::string formatMoneyA(double amount) {
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << amount;
        return "$" + ss.str();
    }

    // Show Usr ID | Name
    void listAllUsers() {
        std::vector<auth::User> users = auth::loadUsers();
        std::cout << "\n" << termcolor::cyan;
        printCenteredA("======== ALL USERS ========");
        printCenteredA("User ID          | Username");
        printCenteredA("--------------------------");
        std::cout << termcolor::reset;

        if (users.empty()) {
            std::cout << termcolor::yellow;
            printCenteredA("No users found.");
            std::cout << termcolor::reset;
            return;
        }

        for (const auto& u : users) {
            std::cout << termcolor::yellow;
            std::string row = u.id + " | " + u.username;
            printCenteredA(row);
        }
        std::cout << termcolor::reset;
    }

    // Enter ID
    void editUser() {
        std::vector<auth::User> users = auth::loadUsers();
        listAllUsers();

        std::string idNum;
        std::cout << "\n" << std::string((ADMIN_CONSOLE_WIDTH - 26) / 2, ' ') << "Enter User ID number: ";
        std::cin >> idNum;

        std::string fullId = "USR-" + idNum;

        bool found = false;
        for (auto& u : users) {
            if (u.id == fullId) {
                found = true;
                std::cout << termcolor::cyan;
                printCenteredA("Current username: " + u.username);
                std::cout << termcolor::reset;

                std::string newUser;
                std::cout << std::string((ADMIN_CONSOLE_WIDTH - 24) / 2, ' ') << "Enter new username: ";
                std::cin >> newUser;

                if (!newUser.empty() && newUser != "-") {
                    u.username = newUser;
                    auth::saveUsers(users);
                    std::cout << termcolor::green;
                    printCenteredA("Username updated successfully.");
                    std::cout << termcolor::reset;
                } else {
                    std::cout << termcolor::yellow;
                    printCenteredA("No changes made.");
                    std::cout << termcolor::reset;
                }
                break;
            }
        }

        if (!found) {
            std::cout << termcolor::red;
            printCenteredA("User ID not found.");
            std::cout << termcolor::reset;
        }
    }

    // Username For safety
    void deleteUser() {
        std::vector<auth::User> users = auth::loadUsers();
        listAllUsers();

        std::string target;
        std::cout << std::string((ADMIN_CONSOLE_WIDTH - 26) / 2, ' ') << "Enter username to delete: ";
        std::cin >> target;

        auto it = users.begin();
        bool found = false;
        while (it != users.end()) {
            if (it->username == target) {
                it = users.erase(it);
                found = true;
            } else {
                ++it;
            }
        }

        if (found) {
            auth::saveUsers(users);
            std::cout << termcolor::green;
            printCenteredA("User deleted successfully.");
            std::cout << termcolor::reset;
        } else {
            std::cout << termcolor::red;
            printCenteredA("User not found.");
            std::cout << termcolor::reset;
        }
    }

    // View Stats
    void viewStats() {
        std::ifstream file(SESSION_FILE_ADMIN);
        if (!file.is_open()) {
            std::cout << termcolor::red;
            printCenteredA("No session data found.");
            std::cout << termcolor::reset;
            return;
        }

        std::string line;
        std::getline(file, line);

        int totalMinutes = 0;
        double totalPrintScanValue = 0.0;
        std::vector<std::string> usernames;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string uname, date, totalCost, servicesStr;
            std::getline(ss, uname, ',');
            std::getline(ss, date, ',');
            std::getline(ss, totalCost, ',');
            std::getline(ss, servicesStr);

            bool found = false;
            for (const auto& u : usernames) if (u == uname) { found = true; break; }
            if (!found) usernames.push_back(uname);

            std::stringstream sv(servicesStr);
            std::string entry;
            while (std::getline(sv, entry, ';')) {
                std::stringstream se(entry);
                std::string name, mins, cost;
                std::getline(se, name, '|');
                std::getline(se, mins, '|');
                std::getline(se, cost, '|');
                if (!mins.empty()) totalMinutes += std::stoi(mins);
                if ((name == "Print" || name == "Scan") && !cost.empty()) {
                    totalPrintScanValue += std::stod(cost);
                }
            }
        }

        std::cout << "\n" << termcolor::cyan;
        printCenteredA("======== SYSTEM STATS ========");
        std::cout << termcolor::yellow;
        printCenteredA("Total Registered Users: " + std::to_string(auth::loadUsers().size()));
        printCenteredA("Users With Sessions   : " + std::to_string(usernames.size()));
        printCenteredA("Total Time (all users): " + std::to_string(totalMinutes) + " mins");
        printCenteredA("Total Print+Scan Value: " + formatMoneyA(totalPrintScanValue));
        std::cout << termcolor::reset;
    }

    // Register New Admin
    void registerNewAdmin() {
        std::string username, password;

        std::cout << "\n" << termcolor::cyan;
        printCenteredA("===== REGISTER NEW ADMIN =====");
        std::cout << termcolor::reset << "\n";

        std::cout << std::string((ADMIN_CONSOLE_WIDTH - 22) / 2, ' ') << "New admin username: ";
        std::cin >> username;

        std::cout << std::string((ADMIN_CONSOLE_WIDTH - 22) / 2, ' ') << "New admin password: ";
        std::cin >> password;

        if (adminauth::registerAdmin(username, password)) {
            std::cout << termcolor::green;
            printCenteredA("Admin \"" + username + "\" registered successfully!");
            std::cout << termcolor::reset;
        } else {
            std::cout << termcolor::red;
            printCenteredA("Admin username already exists.");
            std::cout << termcolor::reset;
        }
    }

    // Admin Menu Loop
    void showAdminMenu(const std::string& adminUsername) {
        int choice;
        bool loggedIn = true;

        do {
            std::cout << "\n" << termcolor::cyan;
            printCenteredA("=====================================");
            printCenteredA("            ADMIN MENU               ");
            printCenteredA("=====================================");
            std::cout << termcolor::yellow;
            printCenteredA("1. View All Users");
            printCenteredA("2. Edit a User");
            printCenteredA("3. Delete a User");
            printCenteredA("4. View System Stats");
            printCenteredA("5. Register New Admin");
            printCenteredA("6. Logout");
            std::cout << termcolor::reset;

            std::cout << std::string((ADMIN_CONSOLE_WIDTH - 18) / 2, ' ') << "Choose an option: ";
            std::cin >> choice;
            std::cout << "\n";

            switch (choice) {
                case 1: listAllUsers();     break;
                case 2: editUser();         break;
                case 3: deleteUser();       break;
                case 4: viewStats();        break;
                case 5: registerNewAdmin(); break;
                case 6:
                    std::cout << termcolor::cyan;
                    printCenteredA("Admin logged out.");
                    std::cout << termcolor::reset;
                    loggedIn = false;
                    break;
                default:
                    std::cout << termcolor::red;
                    printCenteredA("Invalid choice.");
                    std::cout << termcolor::reset;
            }
        } while (loggedIn);
    }
}
