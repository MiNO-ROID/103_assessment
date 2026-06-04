cmake_minimum_required(VERSION 3.20)
project(103_assessment)

set(CMAKE_CXX_STANDARD 20)

add_executable(103_assessment
        main.cpp
        Menu/menu.cpp
        Menu/session.cpp
        Menu/admin_menu.cpp
        Features/logout.cpp
        Features/user_auth.cpp
        Features/session_manager.cpp
        Features/admin_auth.cpp
)

target_include_directories(103_assessment PRIVATE
        ${CMAKE_SOURCE_DIR}/Header
)

file(COPY ${CMAKE_SOURCE_DIR}/CSV DESTINATION ${CMAKE_BINARY_DIR})
