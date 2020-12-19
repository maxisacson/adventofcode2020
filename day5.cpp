#include "gtest/gtest.h"
#include "fmt/core.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>

int getSeatId(const std::string& line) {
    int row = 0;
    int col = 0;
    for (int i = 0; i < 7; ++i) {
        int bit = line[i] == 'B' ? 1 : 0;
        row |= bit << (6-i);
    }
    for (int i = 0; i < 3; ++i) {
        int bit = line[i+7] == 'R' ? 1 : 0;
        col |= bit << (2-i);
    }
    return row * 8 + col;
}

TEST(Day5, Task1) {
    std::ifstream input("../input/day5.txt");
    EXPECT_TRUE(input.is_open());

    int id_max = -1;
    std::string line;
    while(std::getline(input, line)) {
        EXPECT_EQ(line.size(), 10);
        auto id = getSeatId(line);
        id_max = std::max(id, id_max);
    }
    EXPECT_LE(id_max, 127*8+7);
    fmt::print("max id = {}\n", id_max);
}

TEST(Day5, Task2) {
    std::ifstream input("../input/day5.txt");
    EXPECT_TRUE(input.is_open());

    std::string line;
    std::array<int, 127*8+7+1> seats{};
    while(std::getline(input, line)) {
        EXPECT_EQ(line.size(), 10);
        auto id = getSeatId(line);
        EXPECT_EQ(seats[id], 0);
        seats[id] = 1;
    }
    int my_seat = -1;
    for (int i = 1; i < seats.size()-1; ++i) {
        if (seats[i] == 0 && seats[i-1] == 1 && seats[i+1] == 1) {
            EXPECT_EQ(my_seat, -1);
            my_seat = i;
        }
    }
    fmt::print("my seat = {}\n", my_seat);
}
