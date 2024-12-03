#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

std::string Day3::part1(std::istream& input)
{
    std::string line;
    std::regex re(R"(mul\((\d+),(\d+)\))");
    int sum = 0;
    while (getline(input, line)) {
        std::smatch match;

        auto it = std::sregex_iterator(line.begin(), line.end(), re);
        auto end = std::sregex_iterator();
        for (; it != end; ++it) {
            match = *it;
            int a = std::stoi(match[1]);
            int b = std::stoi(match[2]);
            sum += a * b;
        }
    }
    return std::to_string(sum);
}

std::string Day3::part2(std::istream& input)
{
    std::string line;
    std::regex re(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
    int sum = 0;
    bool enabled = true;
    while (getline(input, line)) {
        std::smatch match;

        auto it = std::sregex_iterator(line.begin(), line.end(), re);
        auto end = std::sregex_iterator();
        for (; it != end; ++it) {
            match = *it;
            if (match[0] == "do()") {
                enabled = true;
            } else if (match[0] == "don't()") {
                enabled = false;
            } else if (enabled) {
                int a = std::stoi(match[1]);
                int b = std::stoi(match[2]);
                sum += a * b;
            }
        }
    }
    return std::to_string(sum);
}