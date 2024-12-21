#include <algorithm>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day22 {
std::string part1(std::istream& input)
{
    throw std::runtime_error("not implemented");
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day22::description()
{
    DayDescription description { 22, 2024 };
    description.part1 = day22::part1;
    description.part2 = day22::part2;
    // description.part1_test_result = "";
    // description.part2_test_result = "";
    // description.test_input = "";
    return description;
}
