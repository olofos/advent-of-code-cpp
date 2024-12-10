#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day2 {
std::vector<std::vector<int>> parse(std::istream& input)
{
    std::string line;
    std::vector<std::vector<int>> numbers;
    while (getline(input, line)) {
        std::istringstream is(line);
        numbers.push_back(
            std::vector<int>(std::istream_iterator<int>(is), std::istream_iterator<int>()));
    }
    return numbers;
}

bool is_safe(const std::vector<int>& row, size_t size)
{
    auto [increasing, decreasing] = std::transform_reduce(
        row.begin(),
        row.begin() + size - 1,
        row.begin() + 1, std::pair { true, true },
        [](std::pair<bool, bool> a, std::pair<bool, bool> b) { return std::pair<bool, bool> { a.first && b.first, a.second && b.second }; },
        [](int a, int b) { return std::pair<bool, bool> { (a > b) && (a <= b + 3), (b > a) && (b <= a + 3) }; });

    return increasing || decreasing;
}

std::string part1(std::istream& input)
{
    auto numbers = parse(input);
    auto count = std::count_if(numbers.begin(), numbers.end(), [](auto row) { return is_safe(row, row.size()); });

    return std::to_string(count);
}

std::string part2(std::istream& input)
{
    auto numbers = parse(input);
    int count = 0;
    for (auto& row : numbers) {
        bool safe = false;

        for (unsigned i = 0; i < row.size(); i++) {
            std::iter_swap(row.end() - i - 1, row.end() - 1);
            if (is_safe(row, row.size() - 1)) {
                safe = true;
            }
        }

        if (safe) {
            count++;
        }
    }

    return std::to_string(count);
}
}

DayDescription Day2::description()
{
    DayDescription description { 2, 2024 };
    description.part1 = day2::part1;
    description.part2 = day2::part2;
    description.part1_test_result = "2";
    description.part2_test_result = "4";
    description.test_input = "7 6 4 2 1\n1 2 7 8 9\n9 7 6 2 1\n1 3 2 4 5\n8 6 4 4 1\n1 3 6 7 9\n";
    return description;
}