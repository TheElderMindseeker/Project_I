cmake_minimum_required(VERSION 3.8)
project(Project_I)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Date.cpp Date.hpp Student.cpp Student.hpp)
add_executable(Project_I ${SOURCE_FILES})