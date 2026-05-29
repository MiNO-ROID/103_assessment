#include <iostream>
#include <string>
#include "menu.h"
#include "termcolor.hpp"

using namespace std;

const int CONSOLE_WIDTH = 80;

void printCentered(const string& text) {
    int padding = (CONSOLE_WIDTH - static_cast<int>(text.length())) / 2;

    if (padding < 0) {
        padding = 0;
    }

    cout << string(padding, ' ') << text << "\n";
}

void printCenteredNoEnd(const string& text) {
    int padding = (CONSOLE_WIDTH - static_cast<int>(text.length())) / 2;

    if (padding < 0) {
        padding = 0;
    }

    cout << string(padding, ' ') << text;
}

void showTitle() {
    string blah = R"(
                        ___ _  ____   ___    ___ _  _ ___
                       / __| |/ /\ \ / / |  |_ _| \| | __|
                       \__ \ ' <  \ V /| |__ | || .` | _|
                       |___/_|\_\  |_| |____|___|_|\_|___|
)";

    cout << termcolor::cyan << blah << termcolor::reset << endl;

    cout << "\n";
    cout << termcolor::yellow;
    printCentered("----Cyber Cafe Automated Billing System----");
    printCentered("~Auckland CBD~");

    cout << "\n";
    cout << termcolor::cyan;
    printCentered("===============================================");
    cout << termcolor::reset << "\n";
}

void showMenu() {
    showTitle();

    cout << termcolor::yellow;
    printCentered("+-----------------+ +-----------------+");
    printCentered("|                 | |                 |");
    printCentered("|   1. Register   | |    2. Login     |");
    printCentered("|                 | |                 |");
    printCentered("+-----------------+ +-----------------+");
    cout << "\n";
    printCentered("+-----------------+ +-----------------+");
    printCentered("|                 | |                 |");
    printCentered("|  3. Admin Login | |     4. Exit     |");
    printCentered("|                 | |                 |");
    printCentered("+-----------------+ +-----------------+");
    cout << termcolor::reset << "\n";

    printCenteredNoEnd("Enter choice: ");
}

void registerUser() {
    cout << "\n";
    cout << termcolor::yellow;
    printCentered("[Register - coming soon]");
    cout << termcolor::reset << "\n";
}

void loginUser() {
    cout << "\n";
    cout << termcolor::yellow;
    printCentered("[Login - coming soon]");
    cout << termcolor::reset << "\n";
}

void adminLogin() {
    cout << "\n";
    cout << termcolor::yellow;
    printCentered("[Admin Login - coming soon]");
    cout << termcolor::reset << "\n";
}