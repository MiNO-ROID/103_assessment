#include <iostream>
#include "session.h"

namespace v2 {

    void showLoggedInMenu() {
        int choice;

        do {
            std::cout << "\n=====================================\n";
            std::cout << "             USER MENU               \n";
            std::cout << "=====================================\n";
            std::cout << "1. Start Cafe Session\n";
            std::cout << "2. End Cafe Session\n";
            std::cout << "3. View Session History\n";
            std::cout << "4. Logout\n";
            std::cout << "Choose an option: ";
            std::cin >> choice;

            std::cout << "\n";

            switch (choice) {
                case 1:
                    std::cout << "Starting cafe session...\n";
                    break;
                case 2:
                    std::cout << "Ending cafe session...\n";
                    break;
                case 3:
                    std::cout << "Viewing session history...\n";
                    break;
                case 4:
                    std::cout << "Logging out...\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 4);
    }

}