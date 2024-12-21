#include <algorithm>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day24 {
std::string part1(std::istream& input)
{
    throw std::runtime_error("not implemented");
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day24::description()
{
    DayDescription description { 24, 2024 };
    description.part1 = day24::part1;
    description.part2 = day24::part2;
    // description.part1_test_result = "";
    // description.part2_test_result = "";
    // description.test_input = "";
    return description;
}
