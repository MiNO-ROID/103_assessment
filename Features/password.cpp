#include "password.h"
#include <string>
#include <random>
#include <algorithm>

namespace passgen {

    std::string generatePassword() {
        std::string upperCase   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string lowerCase   = "abcdefghijklmnopqrstuvwxyz";
        std::string number  = "0123456789";
        std::string specialchar = "!@#$%^&*";
        std::string all     = upperCase + lowerCase + number + specialchar;

        std::random_device rd;
        std::mt19937 gen(rd());

        std::string password = "";
        password += upperCase  [std::uniform_int_distribution<>(0, upperCase.size()   - 1)(gen)];
        password += lowerCase  [std::uniform_int_distribution<>(0, lowerCase.size()   - 1)(gen)];
        password += number [std::uniform_int_distribution<>(0, number.size()  - 1)(gen)];
        password += specialchar [std::uniform_int_distribution<>(0, specialchar.size() - 1)(gen)];

        for (int i = 0; i < 8; i++)
            password += all[std::uniform_int_distribution<>(0, all.size() - 1)(gen)];

        std::shuffle(password.begin(), password.end(), gen);
        return password;
    }

}