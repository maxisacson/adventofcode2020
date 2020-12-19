#include "gtest/gtest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include <fstream>
#include <string>
#include <numeric>

TEST(Day6, Task1) {
    std::ifstream input("../input/day6.txt");
    EXPECT_TRUE(input.is_open());

    int total{};
    std::string line;
    std::array<int, 26> tally{};
    while(input) {
        std::getline(input, line);
        if (line.empty() || !input) {
            // end of group
            total = std::accumulate(std::begin(tally), std::end(tally), total);
            tally = {};
        } else {
            for (const auto& c : line) {
                EXPECT_LE(c, 'z');
                EXPECT_GE(c, 'a');
                tally[c-'a'] = 1;
            }
        }
    }

    fmt::print("total = {}\n", total);
}

TEST(Day6, Task2) {
    std::ifstream input("../input/day6.txt");
    EXPECT_TRUE(input.is_open());

    int total{};
    int group_size{};
    std::string line;
    std::array<int, 26> tally{};
    while(input) {
        std::getline(input, line);
        if (line.empty() || !input) {
            // end of group
            total += std::count(std::begin(tally), std::end(tally), group_size);
            tally = {};
            group_size = {};
        } else {
            for (const auto& c : line) {
                EXPECT_LE(c, 'z');
                EXPECT_GE(c, 'a');
                ++tally[c-'a'];
            }
            ++group_size;
        }
    }

    fmt::print("total = {}\n", total);
}
