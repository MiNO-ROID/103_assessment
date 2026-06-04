#include <iostream>
#include "../Header/logout.h"
#include "../Header/termcolor.hpp"

using namespace std;

const int CONSOLE_WIDTH = 80;

namespace v2 {

    void logoutUser() {
        int padding = (CONSOLE_WIDTH - 38) / 2;
        cout << "\n" << termcolor::cyan;
        cout << string(padding, ' ') << "You have been logged out.\n";
        cout << termcolor::reset << "\n";
    }

}