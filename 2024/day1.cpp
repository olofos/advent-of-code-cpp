#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "days.h"

namespace day1 {
std::pair<std::vector<int>, std::vector<int>> parse(std::istream& input)
{
    int a, b;
    std::vector<int> values1;
    std::vector<int> values2;

    while (input >> a >> b) {
        values1.push_back(a);
        values2.push_back(b);
    }
    std::ranges::sort(values1);
    std::ranges::sort(values2);

    return { values1, values2 };
}

std::string part1(std::istream& input)
{
    auto [values1, values2] = parse(input);

    auto sum = std::transform_reduce(values1.begin(), values1.end(), values2.begin(), 0, std::plus<int>(), [](int a, int b) { return std::abs(a - b); });

    return std::to_string(sum);
}

std::string part2(std::istream& input)
{
    auto [values1, values2] = parse(input);

    auto sum = std::transform_reduce(values1.begin(), values1.end(), 0, std::plus<int>(), [&](int a) {
        return a * static_cast<int>(std::count_if(values2.begin(), values2.end(), [a](int b) { return b == a; }));
    });

    return std::to_string(sum);
}
}

DayDescription Day1::description()
{
    DayDescription description { 1, 2024 };
    description.part1 = day1::part1;
    description.part2 = day1::part2;
    description.part1_test_result = "11";
    description.part2_test_result = "31";
    description.test_input = "3   4\n4   3\n2   5\n1   3\n3   9\n3   3";
    return description;
}