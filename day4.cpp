#include "gtest/gtest.h"
#include "fmt/core.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>

TEST(Day4, Task1) {
    std::ifstream input("../input/day4.txt");
    EXPECT_TRUE(input.is_open());

    std::string line;
    std::set<std::string> keys;
    int valid{};
    while(input) {
        std::getline(input, line);
        if (line.empty() || !input) {
            valid += (keys.size() - keys.count("cid") == 7);
            keys.clear();
        } else {
            int pos{};
            while (pos != std::string::npos) {
                pos = line.find(" ");
                auto tmp = line.substr(0, pos);
                line = line.substr(pos+1, std::string::npos);
                auto key = tmp.substr(0, line.find(":"));
                keys.insert(key);
            }
        }
    }
    fmt::print("{}\n", valid);
}

TEST(Day4, Task2) {
    std::ifstream input("../input/day4.txt");
    EXPECT_TRUE(input.is_open());

    const auto& re_byr = std::regex("\\d{4}");
    const auto& re_iyr = std::regex("\\d{4}");
    const auto& re_eyr = std::regex("\\d{4}");
    const auto& re_hgt = std::regex("(\\d+)(cm|in)");
    const auto& re_hcl = std::regex("#[0-9a-f]{6}");
    const auto& re_ecl = std::regex("amb|blu|brn|gry|grn|hzl|oth");
    const auto& re_pid = std::regex("\\d{9}");

    std::string line;
    std::unordered_map<std::string, std::string> kv;
    int valid{};
    while(input) {
        std::getline(input, line);
        if (line.empty() || !input) {
            if (kv.size() - kv.count("cid") == 7) {
                int n_valid{};
                for (const auto& [key, val] : kv) {
                    const auto between = [](auto x, auto a, auto b) {
                        return x >= a && x <= b;
                    };

                    std::smatch m;
                    if (key == "cid") {
                        // skip
                    } else if (key == "byr" && std::regex_match(val, m, re_byr)) {
                        n_valid += between(std::stoi(m.str()), 1920, 2002);
                    } else if (key == "iyr" && std::regex_match(val, m, re_iyr)) {
                        n_valid += between(std::stoi(m.str()), 2010, 2020);
                    } else if (key == "eyr" && std::regex_match(val, m, re_eyr)) {
                        n_valid += between(std::stoi(m.str()), 2020, 2030);
                    } else if (key == "hgt" && std::regex_match(val, m, re_hgt)) {
                        const auto hgt = std::stoi(m[1].str());
                        const auto& unit = m[2].str();
                        if (unit == "cm") {
                            n_valid += between(hgt, 150, 193);
                        } else if (unit == "in") {
                            n_valid += between(hgt, 59, 76);
                        }
                    } else if (key == "hcl" && std::regex_match(val, m, re_hcl)) {
                        ++n_valid;
                    } else if (key == "ecl" && std::regex_match(val, m, re_ecl)) {
                        ++n_valid;
                    } else if (key == "pid" && std::regex_match(val, m, re_pid)) {
                        ++n_valid;
                    }
                }
                valid += (n_valid == 7);
            }
            kv.clear();
        } else {
            int pos{};
            while (pos != std::string::npos) {
                pos = line.find(" ");
                auto tmp = line.substr(0, pos);
                line = line.substr(pos+1, std::string::npos);
                auto pos2 = line.find(":");
                auto key = tmp.substr(0, pos2);
                auto val = tmp.substr(pos2+1, std::string::npos);
                kv[key] = val;
            }
        }
    }
    fmt::print("{}\n", valid);
}
