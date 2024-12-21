#include <algorithm>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day23 {
std::string part1(std::istream& input)
{
    throw std::runtime_error("not implemented");
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day23::description()
{
    DayDescription description { 23, 2024 };
    description.part1 = day23::part1;
    description.part2 = day23::part2;
    // description.part1_test_result = "";
    // description.part2_test_result = "";
    // description.test_input = "";
    return description;
}
