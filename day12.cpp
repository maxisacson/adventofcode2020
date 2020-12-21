#include "gtest/gtest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include <fstream>
#include <string>
#include <numeric>

struct int2 {
    int x{};
    int y{};
};

constexpr auto north = int2{0,-1};
constexpr auto south = int2{0,1};
constexpr auto east = int2{1,0};
constexpr auto west = int2{-1,0};

int2 rotate(const int2& v, int sign, int angle) {
    angle /= 90;
    int2 r = v;
    for (; angle > 0; --angle) {
        r = {-sign*r.y, sign*r.x};
    }
    return r;
}

TEST(Day12, Task1) {
    std::ifstream input("../input/day12.txt");
    EXPECT_TRUE(input.is_open());

    auto heading = east;
    auto pos = int2{0, 0};

    std::string line;
    while(std::getline(input, line)) {
        auto op = line[0];
        auto arg = std::stoi(line.substr(1, std::string::npos));
        switch(op) {
            case 'N': {
                pos.y -= arg;
            } break;
            case 'S': {
                pos.y += arg;
            } break;
            case 'E': {
                pos.x += arg;
            } break;
            case 'W': {
                pos.x -= arg;
            } break;
            case 'R': {
                heading = rotate(heading, 1, arg);
            } break;
            case 'L': {
                heading = rotate(heading, -1, arg);
            } break;
            case 'F': {
                pos.x += arg * heading.x;
                pos.y += arg * heading.y;
            } break;
            default: {
                FAIL();
            }
        }
    }

    auto dist = std::abs(pos.x) + std::abs(pos.y);
    fmt::print("dist = {}\n", dist);
}

TEST(Day12, Task2) {
    std::ifstream input("../input/day12.txt");
    EXPECT_TRUE(input.is_open());

    auto pos = int2{0, 0};
    auto wp = int2{10, -1};

    std::string line;
    while(std::getline(input, line)) {
        auto op = line[0];
        auto arg = std::stoi(line.substr(1, std::string::npos));
        switch(op) {
            case 'N': {
                wp.y -= arg;
            } break;
            case 'S': {
                wp.y += arg;
            } break;
            case 'E': {
                wp.x += arg;
            } break;
            case 'W': {
                wp.x -= arg;
            } break;
            case 'R': {
                wp = rotate(wp, 1, arg);
            } break;
            case 'L': {
                wp = rotate(wp, -1, arg);
            } break;
            case 'F': {
                pos.x += arg * wp.x;
                pos.y += arg * wp.y;
            } break;
            default: {
                FAIL();
            }
        }
    }

    auto dist = std::abs(pos.x) + std::abs(pos.y);
    fmt::print("dist = {}\n", dist);
}
