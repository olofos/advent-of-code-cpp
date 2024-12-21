#include <algorithm>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day25 {
std::string part1(std::istream& input)
{
    throw std::runtime_error("not implemented");
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day25::description()
{
    DayDescription description { 25, 2024 };
    description.part1 = day25::part1;
    description.part2 = day25::part2;
    // description.part1_test_result = "";
    // description.part2_test_result = "";
    // description.test_input = "";
    return description;
}
