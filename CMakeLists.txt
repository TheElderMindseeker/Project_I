cmake_minimum_required(VERSION 3.8)
project(Project_I)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp date/Date.cpp date/Date.hpp student/Student.cpp student/Student.hpp pill/Pill.cpp pill/Pill.hpp)
add_executable(Project_I ${SOURCE_FILES})