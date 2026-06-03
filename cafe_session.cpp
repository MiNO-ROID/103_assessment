#include <iostream>
#include <string>
#include <ctime>
#include "cafe_session.h"
#include "termcolor.hpp"

const int CONSOLE_WIDTH = 80;

namespace v2 {

    bool sessionActive = false;
    time_t sessionStartTime = 0;

    void printCenteredCS(const std::string& text) {
        int padding = (CONSOLE_WIDTH - static_cast<int>(text.length())) / 2;
        if (padding < 0) padding = 0;
        std::cout << std::string(padding, ' ') << text << "\n";
    }

    void startCafeSession() {
        if (sessionActive) {
            std::cout << termcolor::yellow;
            printCenteredCS("A session is already active!");
            std::cout << termcolor::reset;
            return;
        }

        sessionActive = true;
        sessionStartTime = time(nullptr);

        char timeBuffer[26];
        ctime_s(timeBuffer, sizeof(timeBuffer), &sessionStartTime);

        std::cout << termcolor::green;
        printCenteredCS("=====================================");
        printCenteredCS("      Cafe session started!");
        printCenteredCS("Time started: " + std::string(timeBuffer));
        printCenteredCS("=====================================");
        std::cout << termcolor::reset;
    }
}
