#include <iostream>
#include "menu.h"
using namespace std;

int main() {
    enableColor();

    int choice;
    do {
        showMenu();
        cin >> choice;

        cout << "\n";
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
            case 0:
                cout << "\033[36m" << "     Goodbye! Thank you for visiting Skyline.\n" << "\033[0m";
                break;
            default:
                cout << "\033[31m" << "     Invalid choice. Please try again.\n" << "\033[0m";
        }
        cout << "\n";
    } while (choice != 0);

    return 0;
}