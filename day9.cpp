#include "gtest/gtest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include <fstream>
#include <string>
#include <numeric>


TEST(Day9, Task1) {
    std::ifstream input("../input/day9.txt");
    EXPECT_TRUE(input.is_open());

    std::vector<long long int> numbers{};
    std::string line;
    while(std::getline(input, line)) {
        numbers.push_back(std::stoll(line));
    }

    const auto answer = [&]() {
        for (auto i = 25; i < numbers.size(); ++i) {
            auto current = numbers[i];
            decltype(numbers) prev(std::begin(numbers)+i-25, std::begin(numbers)+i);
            EXPECT_EQ(prev.size(), 25);
            std::sort(std::begin(prev), std::end(prev));

            auto hi = prev.back();
            auto lo = prev.front();

            if (lo >= current || hi + prev[prev.size()-2] < current) {
                return current;
            }

            auto found = false;
            for (auto j = 0; j < prev.size(); ++j) {
                auto tmp = current - prev[j];
                if (tmp > hi || tmp < lo) {
                    continue;
                }
                for (auto k = prev.size()-1; k > j; --k) {
                    if (prev[k] == tmp) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            if (!found) {
                return current;
            }
        }
        return -1ll;
    }();

    EXPECT_NE(answer, -1);
    fmt::print("answer = {}\n", answer);
}

TEST(Day9, Task2) {
    const auto N = 21806024ll; // Number from Task 1

    std::ifstream input("../input/day9.txt");
    EXPECT_TRUE(input.is_open());

    std::vector<long long int> numbers{};
    std::string line;
    while(std::getline(input, line)) {
        numbers.push_back(std::stoll(line));
    }

    size_t i = 0;
    size_t j = 0;
    long long int sum = numbers[0];
    while (sum != N && i < numbers.size()-1 && j < numbers.size()) {
        if (sum > N) {
            while (sum > N && i < j-1) {
                sum -= numbers[i++];
            }
        } else {
            sum += numbers[++j];
        }
    }
    decltype(numbers) tmp(std::begin(numbers)+i, std::begin(numbers)+j+1);
    EXPECT_EQ(std::accumulate(std::begin(tmp), std::end(tmp), 0ll), N);
    std::sort(std::begin(tmp), std::end(tmp));
    fmt::print("answer = {}\n", tmp.front() + tmp.back());
}
