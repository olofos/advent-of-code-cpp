#include <algorithm>
#include <iostream>
#include <istream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day11 {
std::vector<uint64_t> parse(std::istream& input)
{
    uint64_t value;
    std::vector<uint64_t> result;
    while (input >> value) {
        result.push_back(value);
    }
    return result;
}

std::optional<uint64_t> half_power_of_ten(uint64_t n)
{
    uint64_t result = 1;
    for (;;) {
        if (n == 0) {
            return result;
        }
        if (n < 10) {
            return std::nullopt;
        }
        n /= 100;
        result *= 10;
    }
}

std::string part1(std::istream& input)
{
    auto curr = parse(input);
    decltype(curr) prev;

    for (int i = 0; i < 25; i++) {
        prev.swap(curr);
        curr.clear();

        for (auto n : prev) {
            if (n == 0) {
                curr.push_back(1);
            } else {
                std::optional<uint64_t> power = half_power_of_ten(n);
                if (power.has_value()) {
                    curr.push_back(n / power.value());
                    curr.push_back(n % power.value());
                } else {
                    curr.push_back(2024 * n);
                }
            }
        }
    }

    return std::to_string(curr.size());
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day11::description()
{
    DayDescription description { 11, 2024 };
    description.part1 = day11::part1;
    description.part2 = day11::part2;
    description.part1_test_result = "55312";
    // description.part2_test_result = "";
    description.test_input = "125 17";
    return description;
}
