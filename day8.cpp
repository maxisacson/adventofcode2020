#include "gtest/gtest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include <fstream>
#include <string>


TEST(Day8, Task1) {
    std::ifstream input("../input/day8.txt");
    EXPECT_TRUE(input.is_open());

    std::vector<std::pair<std::string, int>> program{};
    std::string line;
    while(std::getline(input, line)) {
        auto op = line.substr(0, 3);
        auto arg = std::stoi(line.substr(4, std::string::npos));
        program.push_back({op, arg});
    }
    std::vector<int> hit_count(program.size(), 0);
    EXPECT_EQ(hit_count.size(), program.size());

    int accumulator = 0;
    int pc = 0;
    while(pc < program.size()) {
        EXPECT_GE(pc, 0);
        EXPECT_LT(pc, program.size());

        const auto& [op, arg] = program[pc];

        ++hit_count[pc];
        if (hit_count[pc] == 2) {
            break;
        }
        EXPECT_LE(hit_count[pc], 1);

        if (op == "nop") {
            ++pc;
        } else if (op == "acc" ) {
            accumulator += arg;
            ++pc;
        } else if (op == "jmp") {
            pc += arg;
        }
    }

    fmt::print("acc = {}\n", accumulator);
}

TEST(Day8, Task2) {
    std::ifstream input("../input/day8.txt");
    EXPECT_TRUE(input.is_open());

    std::vector<std::pair<std::string, int>> program{};
    std::string line;
    while(std::getline(input, line)) {
        auto op = line.substr(0, 3);
        auto arg = std::stoi(line.substr(4, std::string::npos));
        program.push_back({op, arg});
    }

    std::vector<int> idx{};
    for (int i = 0; i < program.size(); ++i) {
        const auto& [op, arg] = program[i];
        if (op == "nop" || op == "jmp") {
            idx.push_back(i);
        }
    }

    int accumulator = 0;
    for (int i = 0; i < idx.size(); ++i) {
        auto tmp = program;
        if (tmp[idx[i]].first == "nop") {
            tmp[idx[i]].first = "jmp";
        } else if (tmp[idx[i]].first == "jmp") {
            tmp[idx[i]].first = "nop";
        }

        std::vector<int> hit_count(tmp.size(), 0);
        EXPECT_EQ(hit_count.size(), tmp.size());

        accumulator = 0;
        bool loop = false;
        int pc = 0;
        while(pc < tmp.size()) {
            EXPECT_GE(pc, 0);
            EXPECT_LT(pc, tmp.size());

            const auto& [op, arg] = tmp[pc];

            ++hit_count[pc];
            if (hit_count[pc] == 2) {
                loop = true;
                break;
            }

            if (op == "nop") {
                ++pc;
            } else if (op == "acc" ) {
                accumulator += arg;
                ++pc;
            } else if (op == "jmp") {
                pc += arg;
            }
        }
        if (!loop) {
            break;
        }
    }

    fmt::print("acc = {}\n", accumulator);
}
