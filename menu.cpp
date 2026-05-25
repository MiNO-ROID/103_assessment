#include "menu.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
void enableColor() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void showTitle() {
    cout << "\033[36m";
    cout << "\n";
    cout << "   _____ _  ____     ___      _____ _   _ ______\n";
    cout << "  / ____| |/ /\\ \\   / / |    |_   _| \\ | |  ____|\n";
    cout << " | (___ | ' /  \\ \\_/ /| |      | | |  \\| | |__\n";
    cout << "  \\___ \\|  <    \\   / | |      | | | . ` |  __|\n";
    cout << "  ____) | . \\    | |  | |____ _| |_| |\\  | |____\n";
    cout << " |_____/|_|\\_\\   |_|  |______|_____|_| \\_|______|\n";
    cout << "\n";
    cout << "\033[33m";
    cout << "          ---  C Y B E R   C A F E  ---\n";
    cout << "           ~  A u c k l a n d  C B D  ~\n";
    cout << "\033[36m";
    cout << "\n";
    cout << "  ================================================\n";
    cout << "\033[0m\n";
}

void showMenu() {
    showTitle();

    string pad = "     ";

    cout << "\033[97m";
    cout << pad << "+-----------------+   +-----------------+\n";
    cout << pad << "|                 |   |                 |\n";
    cout << pad << "|   1. Register   |   |    2. Login     |\n";
    cout << pad << "|                 |   |                 |\n";
    cout << pad << "+-----------------+   +-----------------+\n";
    cout << "\n";
    cout << pad << "+-----------------+   +-----------------+\n";
    cout << pad << "|                 |   |                 |\n";
    cout << pad << "|  3. Admin Login |   |     4. Exit     |\n";
    cout << pad << "|                 |   |                 |\n";
    cout << pad << "+-----------------+   +-----------------+\n";
    cout << "\033[0m";

    cout << "\n" << pad << "   Enter choice: ";
}

void registerUser() {
    cout << "\033[33m\n     [Register - coming soon]\n\033[0m";
}

void loginUser() {
    cout << "\033[33m\n     [Login - coming soon]\n\033[0m";
}

void adminLogin() {
    cout << "\033[33m\n     [Admin Login - coming soon]\n\033[0m";
}