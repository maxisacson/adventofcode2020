#include "gtest/gtest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <numeric>


TEST(Day14, Task1) {
    std::ifstream input("../input/day14.txt");
    EXPECT_TRUE(input.is_open());

    std::unordered_map<long long, long long> mem{};
    std::string mask{};

    std::string line;
    while(std::getline(input, line)) {
        if (line.substr(0, 4) == "mask") {
            mask = line.substr(7, std::string::npos);
            EXPECT_EQ(mask.size(), 36);
        } else if (line.substr(0, 3) == "mem") {
            auto address = std::stoll(line.substr(4, line.find(']')-4));
            auto value = std::stoll(line.substr(line.find('=')+2, std::string::npos));
            for (auto i = 0ull; i < mask.size(); ++i) {
                auto j = mask.size()-1-i;
                switch (mask[i]) {
                    case '0': {
                        auto mask_ = ~(1ull << j);
                        value &= mask_;
                    } break;
                    case '1': {
                        auto mask_ = (1ull << j);
                        value |= mask_;
                    } break;
                }
            }
            mem[address] = value;
        }
    }

    auto sum = std::accumulate(mem.begin(), mem.end(), 0ull,
            [](const auto& result, const auto& kv) { return result + kv.second; });
    fmt::print("sum = {}\n", sum);
}

long long toInt(std::string bits) {
    long long result{};
    auto N = bits.size();
    for (auto i = 0; i < N; ++i) {
        auto j = N-1-i;
        result |= (static_cast<long long>(bits[i]-'0') << j);
    }
    return result;
}

std::vector<long long> expand(std::string address) {
    size_t pos = address.find('X');
    if (pos != std::string::npos) {
        std::vector<long long> result = {};

        address[pos] = '0';
        for (const auto& r : expand(address)) {
            result.push_back(r);
        }

        address[pos] = '1';
        for (const auto& r : expand(address)) {
            result.push_back(r);
        }

        return result;
    }

    return {toInt(address)};
}

TEST(Day14, Task2) {
    std::ifstream input("../input/day14.txt");
    EXPECT_TRUE(input.is_open());

    std::unordered_map<long long, long long> mem{};
    std::string mask{};

    std::string line;
    while(std::getline(input, line)) {
        if (line.substr(0, 4) == "mask") {
            mask = line.substr(7, std::string::npos);
            EXPECT_EQ(mask.size(), 36);
        } else if (line.substr(0, 3) == "mem") {
            auto address = fmt::format("{:0>36b}", std::stoll(line.substr(4, line.find(']')-4)));
            EXPECT_EQ(address.size(), 36);
            auto value = std::stoll(line.substr(line.find('=')+2, std::string::npos));
            for (auto i = 0ull; i < mask.size(); ++i) {
                switch (mask[i]) {
                    case 'X': {
                        address[i] = 'X';
                    } break;
                    case '1': {
                        address[i] = '1';
                    } break;
                }
            }
            auto addresses = expand(address);
            for (auto a : addresses) {
                mem[a] = value;
            }

        }
    }

    auto sum = std::accumulate(mem.begin(), mem.end(), 0ull,
            [](const auto& result, const auto& kv) { return result + kv.second; });
    fmt::print("sum = {}\n", sum);
}
