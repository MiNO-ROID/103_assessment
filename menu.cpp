#include <iostream>
#include <string>
#include "menu.h"
#include "termcolor.hpp"
#include "user_auth.h"
#include "session.h"
#include "admin_auth.h"

using namespace std;

const int CONSOLE_WIDTH = 80;

void printCentered(const string& text) {
    int padding = (CONSOLE_WIDTH - static_cast<int>(text.length())) / 2;
    if (padding < 0) padding = 0;
    cout << string(padding, ' ') << text << "\n";
}

void printCenteredNoEnd(const string& text) {
    int padding = (CONSOLE_WIDTH - static_cast<int>(text.length())) / 2;
    if (padding < 0) padding = 0;
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
    string username, password;

    cout << "\n";
    cout << termcolor::cyan;
    printCentered("===== REGISTER =====");
    cout << termcolor::reset << "\n";

    printCenteredNoEnd("Enter username: ");
    cin >> username;

    printCenteredNoEnd("Enter password: ");
    cin >> password;

    if (auth::registerUser(username, password)) {
        cout << termcolor::green;
        printCentered("Registration successful! You can now login.");
        cout << termcolor::reset << "\n";
    } else {
        cout << termcolor::red;
        printCentered("Username already taken. Try a different one.");
        cout << termcolor::reset << "\n";
    }
}

void loginUser() {
    string username, password;

    cout << "\n";
    cout << termcolor::cyan;
    printCentered("===== LOGIN =====");
    cout << termcolor::reset << "\n";

    printCenteredNoEnd("Enter username: ");
    cin >> username;

    printCenteredNoEnd("Enter password: ");
    cin >> password;

    auth::User loggedInUser;
    if (auth::loginUser(username, password, loggedInUser)) {
        cout << termcolor::green;
        printCentered("Login successful! Welcome, " + loggedInUser.username + "!");
        cout << termcolor::reset << "\n";
        v2::showLoggedInMenu(loggedInUser.username);
    } else {
        cout << termcolor::red;
        printCentered("Invalid username or password. Try again.");
        cout << termcolor::reset << "\n";
    }
}

void adminLogin() {
    string username, password;

    cout << "\n";
    cout << termcolor::cyan;
    printCentered("===== ADMIN LOGIN =====");
    cout << termcolor::reset << "\n";

    printCenteredNoEnd("Enter admin username: ");
    cin >> username;

    printCenteredNoEnd("Enter admin password: ");
    cin >> password;

    if (adminauth::loginAdmin(username, password)) {
        cout << termcolor::green;
        printCentered("Admin login successful! Welcome, " + username + "!");
        cout << termcolor::reset << "\n";
        // Admin menu coming soon
        cout << termcolor::yellow;
        printCentered("[Admin menu - coming soon]");
        cout << termcolor::reset << "\n";
    } else {
        cout << termcolor::red;
        printCentered("Invalid admin credentials. Access denied.");
        cout << termcolor::reset << "\n";
    }
}
