#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace {
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
}

bool is_safe(const std::vector<int>& row, size_t size)
{
    bool increasing = true;
    bool decreasing = true;
    bool safe_step = true;
    for (unsigned i = 0; i < size - 1; i++) {
        int diff = row[i + 1] - row[i];
        if (diff <= 0) {
            increasing = false;
        }
        if (diff >= 0) {
            decreasing = false;
        }
        if (std::abs(diff) > 3) {
            safe_step = false;
        }
    }

    return (increasing || decreasing) && safe_step;
}

std::string Day2::part1(std::istream& input)
{
    auto numbers = parse(input);
    int count = 0;
    for (auto& row : numbers) {
        if (is_safe(row, row.size())) {
            count++;
        }
    }

    return std::to_string(count);
}

std::string Day2::part2(std::istream& input)
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