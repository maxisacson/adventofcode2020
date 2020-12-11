#include "gtest/gtest.h"

#include <fstream>
#include <string>
#include <iostream>

TEST(Day1, Task1) {

    std::ifstream input("../input/day1.txt");
    EXPECT_TRUE(input.is_open());

    std::string line;
    std::vector<int> vals;
    while(std::getline(input, line)) {
        vals.push_back(std::stoi(line));
    }
    EXPECT_GT(vals.size(), 0);

    int a = 0;
    int b = 0;
    bool found = false;
    for (auto i = 0; i < vals.size() && !found; ++i) {
        for (auto j = i; j < vals.size() && !found; ++j) {
            a = vals[i];
            b = vals[j];
            if ((a+b) == 2020) {
                found = true;
            }
        }
    }

    EXPECT_EQ(a+b, 2020);
    std::cout << (a*b) << std::endl;
}


TEST(Day1, Task2) {

    std::ifstream input("../input/day1.txt");
    EXPECT_TRUE(input.is_open());

    std::string line;
    std::vector<int> vals;
    while(std::getline(input, line)) {
        vals.push_back(std::stoi(line));
    }
    EXPECT_GT(vals.size(), 0);

    int a = 0;
    int b = 0;
    int c = 0;
    bool found = false;
    for (auto i = 0; i < vals.size() && !found; ++i) {
        for (auto j = i; j < vals.size() && !found; ++j) {
            for (auto k = j; k < vals.size() && !found; ++k) {
                a = vals[i];
                b = vals[j];
                c = vals[k];
                if ((a+b+c) == 2020) {
                    found = true;
                }
            }
        }
    }

    EXPECT_EQ(a+b+c, 2020);
    std::cout << (a*b*c) << std::endl;
}
