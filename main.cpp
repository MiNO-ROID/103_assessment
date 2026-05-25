#include <iostream>
#include "menu.h"
#include "termcolor.hpp"

using namespace std;

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        cout << "\n\n";

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                cout << termcolor::cyan
                     << "                    Goodbye! Thank you for visiting Skyline.\n"
                     << termcolor::reset;
                break;
            default:
                cout << termcolor::red
                     << "                      Invalid choice. Please try again.\n"
                     << termcolor::reset;
                break;
        }

        cout << "\n";

    } while (choice != 4);

    return 0;

}