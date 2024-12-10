#include <fstream>
#include <numeric>
#include <regex>
#include <string>

#include "days.h"

namespace day3 {
std::string part1(std::istream& input)
{
    std::string line;
    std::regex re(R"(mul\((\d+),(\d+)\))");
    int sum = 0;
    while (std::getline(input, line)) {
        sum += std::transform_reduce(std::sregex_iterator(line.begin(), line.end(), re), std::sregex_iterator(), 0, std::plus<int>(), [](auto m) { return std::stoi(m[1]) * std::stoi(m[2]); });
    }
    return std::to_string(sum);
}

std::string part2(std::istream& input)
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
}

DayDescription Day3::description()
{
    DayDescription description { 3, 2024 };
    description.part1 = day3::part1;
    description.part2 = day3::part2;
    description.part1_test_result = "161";
    description.part2_test_result = "48";
    description.test_input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
    return description;
}
