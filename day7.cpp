#include "gtest/gtest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <set>


using InverseRules = std::unordered_map<std::string, std::set<std::string>>;
using BagRules = std::unordered_map<std::string, std::set<std::pair<int, std::string>>>;

int countBagsInverse(const std::string& current, const InverseRules& inverse_rules,
        std::set<std::string>& counted) {

    if (!inverse_rules.count(current)) {
        return 0;
    }

    const auto& bags = inverse_rules.at(current);

    int count = 0;
    for (const auto& bag : bags) {
        if (!counted.count(bag)) {
            counted.insert(bag);
            count += countBagsInverse(bag, inverse_rules, counted) + 1;
        }
    }

    return count;
}

int countBagsInverse(std::string current, const InverseRules& inverse_rules) {
    std::set<std::string> counted{};
    return countBagsInverse(current, inverse_rules, counted);
}

TEST(Day7, Task1) {
    std::ifstream input("../input/day7.txt");
    EXPECT_TRUE(input.is_open());

    InverseRules inverse_rules{};

    std::regex re("(\\w+\\s\\w+) bags contain (.*)");
    std::regex re2("(\\d+) (\\w+\\s\\w+) bags?[,.]");
    std::string line;
    while(std::getline(input, line)) {
        std::smatch m, m2;
        std::regex_match(line, m, re);
        EXPECT_EQ(m.size(), 3);

        auto line2 = m[2].str();
        while(std::regex_search(line2, m2, re2)) {
            EXPECT_EQ(m2.size(), 3);
            inverse_rules[m2[2].str()].insert(m[1].str());
            line2 = m2.suffix();
        }
    }

    auto count = countBagsInverse("shiny gold", inverse_rules);
    fmt::print("count = {}\n", count);
}

int countBags(const std::string& current, const BagRules& rules) {
    int count = 0;
    if (rules.count(current)) {
        const auto& rule = rules.at(current);
        for (const auto& [amount, color] : rule) {
            count += amount * (1 + countBags(color, rules));
        }
    }
    return count;
}

TEST(Day7, Task2) {
    std::ifstream input("../input/day7.txt");
    EXPECT_TRUE(input.is_open());

    BagRules rules{};

    std::regex re("(\\w+\\s\\w+) bags contain (.*)");
    std::regex re2("(\\d+) (\\w+\\s\\w+) bags?[,.]");
    std::string line;
    while (std::getline(input, line)) {
        std::smatch m, m2;
        std::regex_match(line, m, re);
        EXPECT_EQ(m.size(), 3);

        auto line2 = m[2].str();
        while(std::regex_search(line2, m2, re2)) {
            EXPECT_EQ(m2.size(), 3);
            rules[m[1].str()].insert({std::stoi(m2[1].str()), m2[2].str()});
            line2 = m2.suffix();
        }
    }

    auto count = countBags("shiny gold", rules);
    fmt::print("count = {}\n", count);
}
