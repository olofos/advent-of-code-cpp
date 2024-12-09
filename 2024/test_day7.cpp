#include <catch2/catch_test_macros.hpp>

namespace day7 {
uint64_t get_power_of_ten(uint64_t n);
}

TEST_CASE("get_power_of_ten", "[day7]")
{
    REQUIRE(day7::get_power_of_ten(1) == 10);
    REQUIRE(day7::get_power_of_ten(9) == 10);
    REQUIRE(day7::get_power_of_ten(10) == 100);
    REQUIRE(day7::get_power_of_ten(99) == 100);
    REQUIRE(day7::get_power_of_ten(100) == 1000);
    REQUIRE(day7::get_power_of_ten(999999) == 1000000);
}