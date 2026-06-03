cmake_minimum_required(VERSION 4.1)
project(103_assessment)

set(CMAKE_CXX_STANDARD 20)

add_executable(103_assessment
        main.cpp
        menu.cpp
        session.h
        session.cpp
        logout.h
        logout.cpp
        user_auth.h
        user_auth.cpp
        session_manager.h
        session_manager.cpp
        admin_auth.h
        admin_auth.cpp
        admin_menu.h
        admin_menu.cpp
        termcolor.hpp
)

configure_file(users.csv users.csv COPYONLY)
configure_file(admin.csv admin.csv COPYONLY)
