#include <algorithm>
#include <iomanip>
#include <iostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day22 {
uint32_t next(uint32_t value)
{
    value = (value ^ (value << 6)) & 0x00FFFFFF;
    value = (value ^ (value >> 5)) & 0x00FFFFFF;
    value = (value ^ (value << 11)) & 0x00FFFFFF;
    return value;
}

std::vector<uint32_t> parse(std::istream& input)
{
    std::vector<uint32_t> values;
    uint32_t value;
    while (input >> value) {
        values.push_back(value);
    }
    return values;
}

std::string part1(std::istream& input)
{
    auto values = parse(input);

    uint64_t sum = 0;
    for (auto value : values) {
        for (int i = 0; i < 2000; i++) {
            value = next(value);
        }
        sum += value;
    }

    return std::to_string(sum);
}

std::string part2(std::istream& input)
{
    auto values = parse(input);

    std::map<uint32_t, uint32_t> sums;

    for (auto value : values) {
        std::set<uint32_t> seen {};
        uint32_t differences = 0;
        int32_t prev = value % 10;
        for (int i = 0; i < 2000; i++) {
            value = next(value);
            int32_t price = value % 10;
            differences = (differences << 8) | static_cast<uint8_t>((price - prev) & 0xFF);
            if (i > 3) {
                if (!seen.contains(differences)) {
                    sums[differences] += price;
                    seen.insert(differences);
                }
            }
            prev = price;
        }
    }

    uint32_t max = 0;
    for (auto& [key, sum] : sums) {
        max = std::max(max, sum);
    }

    return std::to_string(max);
}
}

DayDescription Day22::description()
{
    DayDescription description { 22, 2024 };
    description.part1 = day22::part1;
    description.part2 = day22::part2;
    description.part1_test_result = "37990510";
    description.part2_test_result = "23";
    description.test_input = "1\n2\n3\n2024";
    return description;
}
