#include "gtest/gtest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include <fstream>
#include <string>
#include <numeric>


TEST(Day11, Task1) {
    std::ifstream input("../input/day11.txt");
    EXPECT_TRUE(input.is_open());

    std::vector<std::vector<char>> seats{};
    std::string line;
    while(std::getline(input, line)) {
        seats.emplace_back(line.begin(), line.end());
    }
    auto next = seats;

    auto countNeighbours = [&](auto row, auto col) {
        int count = 0;
        for (auto i = -1; i <= 1; ++i) {
            for (auto j = -1; j <= 1; ++j) {
                const auto i_ = row + i;
                const auto j_ = col + j;
                if (!(i == 0 && j == 0) &&
                        i_ >= 0 && i_ < seats.size() &&
                        j_ >= 0 && j_ < seats[0].size()) {
                    count += (seats[i_][j_] == '#');
                }
            }
        }
        return count;
    };

    int changed = seats.size()*seats[0].size();
    int occupied = 0;
    while (changed > 0) {
        changed = seats.size()*seats[0].size();
        occupied = 0;
        for (int row = 0; row < seats.size(); ++row) {
            for (int col = 0; col < seats[0].size(); ++col) {
                int n = countNeighbours(row, col);
                EXPECT_LE(n, 8);
                const auto seat = seats[row][col];
                occupied += (seat == '#');
                if (seat == 'L' && n == 0) {
                    next[row][col] = '#';
                } else if (seat == '#' && n >= 4) {
                    next[row][col] = 'L';
                } else {
                    next[row][col] = seat;
                    --changed;
                }
            }
        }
        std::swap(seats, next);
    }

    fmt::print("occupied = {}\n", occupied);
}

TEST(Day11, Task2) {
    std::ifstream input("../input/day11.txt");
    EXPECT_TRUE(input.is_open());

    std::vector<std::vector<char>> seats{};
    std::string line;
    while(std::getline(input, line)) {
        seats.emplace_back(line.begin(), line.end());
    }
    auto next = seats;

    auto countNeighbours = [&](auto row, auto col) {
        int count = 0;
        for (auto i = -1; i <= 1; ++i) {
            for (auto j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }
                auto i_ = row + i;
                auto j_ = col + j;
                while (i_ >= 0 && i_ < seats.size() &&
                        j_ >= 0 && j_ < seats[0].size()) {
                    if (seats[i_][j_] == '#') {
                        ++count;
                        break;
                    } else if (seats[i_][j_] == 'L') {
                        break;
                    }
                    i_ += i;
                    j_ += j;
                }
            }
        }
        return count;
    };

    int changed = seats.size()*seats[0].size();
    int occupied = 0;
    while (changed > 0) {
        changed = seats.size()*seats[0].size();
        occupied = 0;
        for (int row = 0; row < seats.size(); ++row) {
            for (int col = 0; col < seats[0].size(); ++col) {
                int n = countNeighbours(row, col);
                EXPECT_LE(n, 8);
                const auto seat = seats[row][col];
                occupied += (seat == '#');
                if (seat == 'L' && n == 0) {
                    next[row][col] = '#';
                } else if (seat == '#' && n >= 5) {
                    next[row][col] = 'L';
                } else {
                    next[row][col] = seat;
                    --changed;
                }
            }
        }
        std::swap(seats, next);
    }

    fmt::print("occupied = {}\n", occupied);
}
