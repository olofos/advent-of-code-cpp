#include <algorithm>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"
#include "util.h"

namespace day10 {
using Point = aoc::Point;

template <typename T>
std::size_t count_paths(const std::vector<std::string>& lines)
{
    std::map<Point, T> prev;
    std::map<Point, T> curr;

    for (unsigned y = 1; y < lines.size() - 1; y++) {
        for (unsigned x = 1; x < lines[y].size() - 1; x++) {
            if (lines[y][x] == '9') {
                curr[{ x, y }] = T({ x, y });
            }
        }
    }

    for (char c = '8'; c >= '0'; c--) {
        prev.swap(curr);
        curr.clear();

        for (unsigned y = 1; y < lines.size() - 1; y++) {
            for (unsigned x = 1; x < lines[y].size() - 1; x++) {
                if (lines[y][x] == c) {
                    curr[{ x, y }] += prev[{ x + 1, y }];
                    curr[{ x, y }] += prev[{ x - 1, y }];
                    curr[{ x, y }] += prev[{ x, y + 1 }];
                    curr[{ x, y }] += prev[{ x, y - 1 }];
                }
            }
        }
    }

    auto count = std::accumulate(curr.begin(), curr.end(), std::size_t {}, [&](auto sum, auto& p) { return sum + p.second; });
    return count;
}

class SetAccumulator {
    std::set<Point> values;

public:
    SetAccumulator() { }
    SetAccumulator(Point p)
        : values { p }
    {
    }
    void operator+=(const SetAccumulator& other) { values.insert(other.values.begin(), other.values.end()); }
    operator std::size_t() const { return values.size(); }
};

class ValueAccumulator {
    std::size_t value;

public:
    ValueAccumulator()
        : value(0)
    {
    }
    ValueAccumulator(Point)
        : value(1)
    {
    }
    void insert(Point) { value += 1; }
    void operator+=(const ValueAccumulator& other) { value += other.value; }
    operator std::size_t() const { return value; }
};

std::string
part1(std::istream& input)
{
    std::vector<std::string> lines = aoc::read_lines_with_border(input);
    auto count = count_paths<SetAccumulator>(lines);
    return std::to_string(count);
}

std::string part2(std::istream& input)
{
    std::vector<std::string> lines = aoc::read_lines_with_border(input);
    auto count = count_paths<ValueAccumulator>(lines);
    return std::to_string(count);
}
}

DayDescription Day10::description()
{
    DayDescription description { 10, 2024 };
    description.part1 = day10::part1;
    description.part2 = day10::part2;
    description.part1_test_result = "36";
    description.part2_test_result = "81";
    description.test_input = "89010123\n78121874\n87430965\n96549874\n45678903\n32019012\n01329801\n10456732\n";
    return description;
}
