#include <algorithm>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day11 {
std::map<uint64_t, uint64_t> parse(std::istream& input)
{
    uint64_t value;
    std::map<uint64_t, uint64_t> result;
    while (input >> value) {
        result[value] += 1;
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

std::map<uint64_t, uint64_t> step(std::map<uint64_t, uint64_t> prev)
{
    std::map<uint64_t, uint64_t> curr;

    for (auto& [n, count] : prev) {
        if (n == 0) {
            curr[1] += count;
        } else {
            std::optional<uint64_t> power = half_power_of_ten(n);
            if (power.has_value()) {
                curr[n / power.value()] += count;
                curr[n % power.value()] += count;
            } else {
                curr[2024 * n] += count;
            }
        }
    }

    return curr;
}

std::string part1(std::istream& input)
{
    auto counts = parse(input);

    for (int i = 0; i < 25; i++) {
        counts = step(counts);
    }

    auto count = std::accumulate(counts.begin(), counts.end(), uint64_t {}, [](auto a, auto b) { return a + b.second; });

    return std::to_string(count);
}

std::string part2(std::istream& input)
{
    auto counts = parse(input);

    for (int i = 0; i < 75; i++) {
        counts = step(counts);
    }

    auto count = std::accumulate(counts.begin(), counts.end(), uint64_t {}, [](auto a, auto b) { return a + b.second; });

    return std::to_string(count);
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
