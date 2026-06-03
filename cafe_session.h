#pragma once
#include <ctime>

namespace v2 {
    extern bool sessionActive;
    extern time_t sessionStartTime;

    void startCafeSession();
}
