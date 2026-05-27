#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include "menu.h"
#include "termcolor.hpp"

using namespace std;2

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
    vector<string> logo = {
        " _____ _  ____     ___      _____ _   _ ______ ",
        "/ ____| |/ /\\ \\   / / |    |_   _| \\ | |  ____|",
        "| (___ | ' /  \\ \\_/ /| |      | | |  \\| | |__   ",
        "\\___ \\|  <    \\   / | |      | | | . ` |  __|  ",
        " ____) | . \\    | |  | |____ _| |_| |\\  | |____ ",
        "|_____/|_|\\_\\   |_|  |______|_____|_| \\_|______|"
    };
    cout << "\n" << termcolor::cyan;
    for (const string& row : logo) printCentered(row);
    cout << "\n" << termcolor::yellow;
    printCentered("Cyber Cafe");
    printCentered("Auckland CBD");
    cout << "\n" << termcolor::cyan;
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

string generateUserID() {
    return "U" + to_string(time(nullptr));
}

// Email format validation
bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    if (atPos == string::npos || atPos == 0) return false;
    size_t dotPos = email.find('.', atPos);
    if (dotPos == string::npos || dotPos == atPos + 1) return false;
    if (dotPos == email.length() - 1) return false;
    return true;
}

// Password best-practice validation
bool isValidPassword(const string& pw) {
    if (pw.size() < 8) return false;
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char c : pw) {
        if (isupper(c))      hasUpper   = true;
        else if (islower(c)) hasLower   = true;
        else if (isdigit(c)) hasDigit   = true;
        else                 hasSpecial = true;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

string hashPassword(const string& pw) {
    unsigned long hash = 5381;
    for (char c : pw) hash = ((hash << 5) + hash) + c;
    return to_string(hash);
}

void saveUser(const string& id, const string& name,
              const string& email, const string& passwordHash) {
    ofstream f("users.txt", ios::app);
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&now));
    f << id << "|" << name << "|" << email << "|"
      << passwordHash << "|" << buf << "\n";
}

// Check if email already registered
bool emailExists(const string& email) {
    ifstream f("users.txt");
    string line;
    while (getline(f, line)) {
        istringstream ss(line);
        string id, name, storedEmail;
        getline(ss, id,          '|');
        getline(ss, name,        '|');
        getline(ss, storedEmail, '|');
        if (storedEmail == email) return true;
    }
    return false;
}

void registerUser() {
    cout << "\n" << termcolor::cyan;
    printCentered("[ REGISTER ]");
    cout << termcolor::reset << "\n";

    string name, email, password;

    printCenteredNoEnd("Full Name : ");
    cin.ignore();
    getline(cin, name);
    if (name.empty()) {
        cout << termcolor::red;
        printCentered("Name cannot be empty.");
        cout << termcolor::reset;
        cout << "\n"; printCenteredNoEnd("Press Enter to continue...");
        cin.get(); return;
    }

    printCenteredNoEnd("Email     : ");
    getline(cin, email);
    if (!isValidEmail(email)) {
        cout << termcolor::red;
        printCentered("Invalid email format. Example: user@example.com");
        cout << termcolor::reset;
        cout << "\n"; printCenteredNoEnd("Press Enter to continue...");
        cin.get(); return;
    }
    if (emailExists(email)) {
        cout << termcolor::red;
        printCentered("Email already registered.");
        cout << termcolor::reset;
        cout << "\n"; printCenteredNoEnd("Press Enter to continue...");
        cin.get(); return;
    }

    printCenteredNoEnd("Password  : ");
    getline(cin, password);
    if (!isValidPassword(password)) {
        cout << termcolor::red;
        printCentered("Weak password!");
        printCentered("Need 8+ chars, uppercase, lowercase, digit & special character.");
        cout << termcolor::reset;
        cout << "\n"; printCenteredNoEnd("Press Enter to continue...");
        cin.get(); return;
    }

    string id = generateUserID();

    saveUser(id, name, email, hashPassword(password));

    cout << "\n" << termcolor::green;
    printCentered("Registration successful!");
    cout << termcolor::reset;
    printCentered("Your User ID : " + id);

    cout << "\n"; printCenteredNoEnd("Press Enter to continue...");
    cin.get();
}

void loginUser() {
    cout << "\n" << termcolor::cyan;
    printCentered("[ LOGIN ]");
    cout << termcolor::reset << "\n";

    string email, password;
    printCenteredNoEnd("Email    : ");
    cin.ignore();
    getline(cin, email);
    printCenteredNoEnd("Password : ");
    getline(cin, password);

    ifstream f("users.txt");
    string line;
    bool found = false;
    string userName, userID;

    while (getline(f, line)) {
        if (line.empty()) continue;
        istringstream ss(line);
        string id, name, storedEmail, storedHash;
        getline(ss, id,          '|');
        getline(ss, name,        '|');
        getline(ss, storedEmail, '|');
        getline(ss, storedHash,  '|');
        if (storedEmail == email && storedHash == hashPassword(password)) {
            found    = true;
            userName = name;
            userID   = id;
            break;
        }
    }

    if (!found) {
        cout << termcolor::red;
        printCentered("Invalid email or password.");
        cout << termcolor::reset;
    } else {
        cout << termcolor::green;
        printCentered("Login successful! Welcome, " + userName + "!");
        printCentered("User ID: " + userID);
        cout << termcolor::reset;
    }

    cout << "\n"; printCenteredNoEnd("Press Enter to continue...");
    cin.ignore(); cin.get();
}

void adminLogin() {
    cout << "\n" << termcolor::cyan;
}
