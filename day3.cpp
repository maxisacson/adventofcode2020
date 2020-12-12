#include "gtest/gtest.h"

#include <fstream>
#include <string>
#include <numeric>
#include <iostream>

TEST(Day3, Task1) {
    std::ifstream input("../input/day3.txt");
    EXPECT_TRUE(input.is_open());

    int x = 0;
    int count = 0;
    std::string line;
    while(std::getline(input, line)) {
        count += line[x] == '#';
        x = (x + 3) % line.size();
    }
    std::cout << count << std::endl;
}


TEST(Day3, Task2) {
    std::ifstream input("../input/day3.txt");
    EXPECT_TRUE(input.is_open());

    std::array<int, 5> x{};
    std::array<long int, 5> count{};
    std::array<int, 5> stride{1, 3, 5, 7, 1};
    auto y = 0;
    std::string line;
    while(std::getline(input, line)) {
        for (auto i = 0; i < 5; ++i) {
            if (i < 4 || y%2 == 0) {
                count[i] += line[x[i]] == '#';
                x[i] = (x[i] + stride[i]) % line.size();
            }
        }
        ++y;
    }
    auto prod = std::accumulate(std::begin(count), std::end(count), 1l,
            [](const auto& a, const auto& b) { return a * b; });

    std::cout << prod << std::endl;
}
