#include <iostream>
#include <string>
#include "session.h"
#include "logout.h"
#include "session_manager.h"
#include "termcolor.hpp"

const int CONSOLE_WIDTH = 80;

void printCenteredSession(const std::string& text) {
    int padding = (CONSOLE_WIDTH - static_cast<int>(text.length())) / 2;
    if (padding < 0) padding = 0;
    std::cout << std::string(padding, ' ') << text << "\n";
}

namespace v2 {

    void showLoggedInMenu(const std::string& username) {
        int choice;
        bool loggedIn = true;

        do {
            std::cout << "\n" << termcolor::cyan;
            printCenteredSession("=====================================");
            printCenteredSession("             USER MENU               ");
            printCenteredSession("=====================================");
            std::cout << termcolor::yellow;
            printCenteredSession("1. Start Cafe Session");
            printCenteredSession("2. View Session History");
            printCenteredSession("3. Logout");
            std::cout << termcolor::reset;

            std::cout << std::string((CONSOLE_WIDTH - 18) / 2, ' ') << "Choose an option: ";
            std::cin >> choice;
            std::cout << "\n";

            switch (choice) {
                case 1:
                    sessions::startCafeSession(username);
                    break;
                case 2:
                    sessions::viewSessionHistory(username);
                    break;
                case 3:
                    v2::logoutUser();
                    loggedIn = false;
                    break;
                default:
                    printCenteredSession("Invalid choice. Please try again.");
            }

        } while (loggedIn);
    }
}
