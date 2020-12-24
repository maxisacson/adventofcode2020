cmake_minimum_required(VERSION 3.10)
project(advent-of-code-2020)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -Wconversion")
endif()

add_subdirectory(third_party/googletest)
add_subdirectory(third_party/fmt)

add_executable(app main.cpp)
add_executable(test test.cpp
    day1.cpp
    day2.cpp
    day3.cpp
    day4.cpp
    day5.cpp
    day6.cpp
    day7.cpp
    day8.cpp
    day9.cpp
    day10.cpp
    day11.cpp
    day12.cpp
    day13.cpp
    day14.cpp)

target_link_libraries(test gtest_main fmt::fmt)
