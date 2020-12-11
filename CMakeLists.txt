cmake_minimum_required(VERSION 3.10)
project(advent-of-code-2020)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/googletest)

add_executable(app main.cpp)

add_executable(test test.cpp
    day1.cpp)
target_link_libraries(test gtest_main)

