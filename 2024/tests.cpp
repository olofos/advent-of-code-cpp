#include <sstream>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "days.h"

using DayTypes = std::tuple<DAYS>;

TEMPLATE_LIST_TEST_CASE("test_part1", "[aoc]", DayTypes)
{
    auto description = TestType {}.description();
    std::stringstream input(description.test_input.value());
    REQUIRE(description.part1_test_result == description.part1(input));
}

TEMPLATE_LIST_TEST_CASE("test_part2", "[aoc]", DayTypes)
{
    auto description = TestType {}.description();
    std::stringstream input(description.test_input.value());
    REQUIRE(description.part2_test_result == description.part2(input));
}