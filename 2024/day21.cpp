#include <algorithm>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day21 {

std::vector<std::string> parse(std::istream& input)
{
    std::string line;
    std::vector<std::string> lines;
    while (getline(input, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::string part1(std::istream& input)
{
    auto lines = parse(input);
    throw std::runtime_error("not implemented");
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day21::description()
{
    DayDescription description { 21, 2024 };
    description.part1 = day21::part1;
    description.part2 = day21::part2;
    // description.part1_test_result = "126384";
    // description.part2_test_result = "";
    // description.test_input = "029A\n980A\n179A\n456A\n379A";
    return description;
}
