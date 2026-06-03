#include <iostream>
#include <string>
#include "session.h"
#include "logout.h"
#include "cafe_session.h"
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
            printCenteredSession("2. End Cafe Session");
            printCenteredSession("3. View Session History");
            printCenteredSession("4. Logout");
            std::cout << termcolor::reset;

            int padding = (CONSOLE_WIDTH - 18) / 2;
            std::cout << std::string(padding, ' ') << "Choose an option: ";
            std::cin >> choice;
            std::cout << "\n";

            switch (choice) {
                case 1:
                    v2::startCafeSession();
                    break;
                case 2:
                    sessions::endSession(username);
                    break;
                case 3:
                    sessions::viewSessionHistory(username);
                    break;
                case 4:
                    v2::logoutUser();
                    loggedIn = false;
                    break;
                default:
                    printCenteredSession("Invalid choice. Please try again.");
            }

        } while (loggedIn);
    }
}
