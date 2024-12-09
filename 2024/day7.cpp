#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <map>
#include <set>
#include <span>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day7 {
std::vector<std::pair<uint64_t, std::vector<uint64_t>>> parse(std::istream& input)
{
    std::vector<std::pair<uint64_t, std::vector<uint64_t>>> result;

    std::string line;
    while (std::getline(input, line)) {
        std::stringstream ss(line);

        uint64_t sum;
        ss >> sum;

        char c;
        ss >> c;

        if (c != ':') {
            throw std::runtime_error("invalid input");
        }

        std::vector<uint64_t> terms;
        uint64_t term;
        while (ss >> term) {
            terms.push_back(term);
        }

        result.push_back(std::make_pair(sum, terms));
    }

    return result;
}

bool check1(uint64_t sum, uint64_t accum, std::span<uint64_t> terms)
{
    if (terms.empty()) {
        return sum == accum;
    }
    return check1(sum, terms[0] + accum, terms.subspan(1)) || check1(sum, accum * terms[0], terms.subspan(1));
}

uint64_t get_power_of_ten(uint64_t n)
{
    return n < 10 ? 10 : get_power_of_ten(n / 10) * 10;
}

bool check2(uint64_t sum, uint64_t accum, std::span<uint64_t> terms)
{
    if (terms.empty()) {
        return sum == accum;
    }
    auto n1 = accum + terms[0];
    auto n2 = accum * terms[0];
    auto n3 = get_power_of_ten(terms[0]) * accum + terms[0];
    return check2(sum, n1, terms.subspan(1)) || check2(sum, n2, terms.subspan(1)) || check2(sum, n3, terms.subspan(1));
}

std::string part1(std::istream& input)
{
    auto list = parse(input);
    uint64_t total = 0;
    for (auto& [sum, terms] : list) {
        if (check1(sum, 0, terms)) {
            total += sum;
        }
    }

    return std::to_string(total);
}

std::string part2(std::istream& input)
{
    auto list = parse(input);
    uint64_t total = 0;
    for (auto& [sum, terms] : list) {
        if (check2(sum, 0, terms)) {
            total += sum;
        }
    }

    return std::to_string(total);
}
}

DayDescription Day7::description()
{
    DayDescription description { 7, 2024 };
    description.part1 = day7::part1;
    description.part2 = day7::part2;
    description.part1_test_result = "3749";
    description.part2_test_result = "11387";
    description.test_input = "190: 10 19\n3267: 81 40 27\n83: 17 5\n156: 15 6\n7290: 6 8 6 15\n161011: 16 10 13\n192: 17 8 14\n21037: 9 7 18 13\n292: 11 6 16 20\n";
    return description;
}
