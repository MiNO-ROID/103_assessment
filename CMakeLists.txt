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
        cafe_session.h
        cafe_session.cpp
        user_auth.h
        user_auth.cpp
        session_manager.h
        session_manager.cpp
        termcolor.hpp
)
