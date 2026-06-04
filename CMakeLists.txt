cmake_minimum_required(VERSION 4.1)
project(103_assessment)

set(CMAKE_CXX_STANDARD 20)

add_executable(103_assessment
        main.cpp
        Menu/menu.cpp
        "Header/session.h"
        Menu/session.cpp
        "Header/logout.h"
        Features/logout.cpp
        "Header/user_auth.h"
        Features/user_auth.cpp
        "Header/session_manager.h"
        Features/session_manager.cpp
        "Header/admin_auth.h"
        Features/admin_auth.cpp
        "Header/admin_menu.h"
        Menu/admin_menu.cpp
        termcolor.hpp
)

configure_file(users.csv users.csv COPYONLY)
configure_file(admin.csv admin.csv COPYONLY)
