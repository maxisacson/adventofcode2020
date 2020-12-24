#include "gtest/gtest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include <fstream>
#include <string>
#include <limits>
#include <numeric>


TEST(Day13, Task1) {
    std::ifstream input("../input/day13.txt");
    EXPECT_TRUE(input.is_open());

    std::string line;
    std::getline(input, line);
    const auto T = std::stoi(line);

    std::getline(input, line);
    std::vector<int> busIDs{};
    while(true) {
        auto pos = line.find(',');
        auto s = line.substr(0, pos);
        if (s != "x") {
            busIDs.push_back(std::stoi(s));
        }
        if (pos == std::string::npos) break;
        line = line.substr(pos+1, std::string::npos);
    }

    int next = 0;
    auto wait = std::numeric_limits<int>::max();
    for (const auto id : busIDs) {
        const auto f = static_cast<float>(T) / static_cast<float>(id);
        const auto n = static_cast<int>(std::ceil(f));
        const auto dt = n*id - T;
        if (dt < wait) {
            next = id;
            wait = dt;
        }
    }

    fmt::print("next = {}\n", next);
    fmt::print("wait = {}\n", wait);
    fmt::print("next*wait = {}\n", next*wait);
}

long long int egcd(long long int a, long long int b,
        long long int& x, long long int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long int x1, y1;
    long long int d = egcd(b, a%b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

auto solveChineseRemainderTheorem(const std::vector<int>& busIDs, const std::vector<int>& offsets) {
    auto N = std::accumulate(busIDs.begin(), busIDs.end(),
            1ull, std::multiplies<long long>());

    // solve the set of Diophantine equations
    // t = a + x*n
    long long t{};
    for (int i = 0; i < busIDs.size(); ++i) {
        long long a = offsets[i];
        long long n = busIDs[i];
        long long x, y;
        auto d = egcd(n, N/n, x, y);
        t += a * y * (N/n);
    }
    while (t < 0) t += N;
    t %= N;

    return t;
}

TEST(Day13, Task2) {
    std::ifstream input("../input/day13.txt");
    EXPECT_TRUE(input.is_open());

    std::string line;
    std::getline(input, line);
    std::getline(input, line);

    std::vector<int> busIDs{};
    std::vector<int> offsets{};
    int offset = 0;
    while(true) {
        auto pos = line.find(',');
        auto s = line.substr(0, pos);
        if (s != "x") {
            busIDs.push_back(std::stoi(s));
            offsets.push_back(offset);
        }
        --offset;
        if (pos == std::string::npos) break;
        line = line.substr(pos+1, std::string::npos);
    }

    auto t = solveChineseRemainderTheorem(busIDs, offsets);
    for (int i = 0; i < offsets.size(); ++i) {
        EXPECT_EQ((t-offsets[i]) % busIDs[i], 0);
    }
    fmt::print("{}\n{}\n", busIDs, offsets);
    fmt::print("t = {}\n", t);
}
