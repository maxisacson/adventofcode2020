#include "gtest/gtest.h"

#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

TEST(Day2, Task1) {
    std::ifstream input("../input/day2.txt");
    EXPECT_TRUE(input.is_open());

    std::string line;
    auto valid = 0;
    while(std::getline(input, line)) {
        auto dash = line.find('-');
        auto col = line.find(':', dash+1);
        auto min = std::stoi(line.substr(0, dash));
        auto max = std::stoi(line.substr(dash+1, col-2));
        char c = line[col-1];
        std::string pw = line.substr(col+2, std::string::npos);
        auto count = std::count(std::begin(pw), std::end(pw), c);
        valid += (count >= min && count <= max);
    }
    std::cout << valid << std::endl;
}


TEST(Day2, Task2) {
    std::ifstream input("../input/day2.txt");
    EXPECT_TRUE(input.is_open());

    std::string line;
    auto valid = 0;
    while(std::getline(input, line)) {
        auto dash = line.find('-');
        auto col = line.find(':', dash+1);
        auto i = std::stoi(line.substr(0, dash)) - 1;
        auto j = std::stoi(line.substr(dash+1, col-2)) - 1;
        char c = line[col-1];
        std::string pw = line.substr(col+2, std::string::npos);
        valid += (pw[i] == c) != (pw[j] == c);
    }
    std::cout << valid << std::endl;
}
