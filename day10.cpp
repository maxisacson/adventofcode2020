#include "gtest/gtest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include <fstream>
#include <string>
#include <numeric>
#include <unordered_map>


TEST(Day10, Task1) {
    std::ifstream input("../input/day10.txt");
    EXPECT_TRUE(input.is_open());

    std::vector<int> adapters{};
    std::string line;
    while(std::getline(input, line)) {
        adapters.push_back(std::stoi(line));
    }

    std::sort(adapters.begin(), adapters.end());
    std::adjacent_difference(adapters.begin(), adapters.end(), adapters.begin());
    int ones = 0;
    int threes = 1; // Account for the final +3 of the device
    for (const auto& a : adapters) {
        ones += (a == 1);
        threes += (a ==3);
    }

    fmt::print("ones * threes = {}\n", ones*threes);
}

long long int connections(int i, const std::vector<int>& adapters,
        std::unordered_map<int, long long int>& cache) {

    int current = (i == -1) ? 0 : adapters[i];

    if (cache.count(current)) {
        return cache[current];
    }

    if (i == adapters.size()-1) {
        return 1;
    }

    long long int n = 0;
    int j = i+1;
    while(j < adapters.size() && (adapters[j] - current) <= 3) {
        n += connections(j++, adapters, cache);
    }

    cache[current] = n;
    return n;
}

TEST(Day10, Task2) {
    std::ifstream input("../input/day10.txt");
    EXPECT_TRUE(input.is_open());

    std::vector<int> adapters{};
    std::string line;
    while(std::getline(input, line)) {
        adapters.push_back(std::stoi(line));
    }

    std::sort(adapters.begin(), adapters.end());
    std::unordered_map<int, long long int> cache{};
    auto n = connections(-1, adapters, cache);
    fmt::print("connections = {}\n", n);
}
