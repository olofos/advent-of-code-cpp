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

std::vector<std::string> read_lines(std::istream& input)
{
    std::string line;
    std::vector<std::string> lines;
    while (getline(input, line)) {
        lines.emplace_back(line);
    }
    return lines;
}

std::vector<std::string> extend(const std::vector<std::string>& lines)
{
    std::vector<std::string> extended;
    extended.reserve(lines.size() + 2);
    extended.push_back(std::string(lines[0].size() + 2, '.'));
    for (const auto& line : lines) {
        extended.emplace_back('.' + line + '.');
    }
    extended.push_back(std::string(lines[0].size() + 2, '.'));

    return extended;
}

template <typename T, typename F1, typename F2, typename F3>
std::size_t count_paths(const std::vector<std::string>& lines, F1 insert_func, F2 accum_func, F3 extract_func)
{
    std::map<Point, T> prev;
    std::map<Point, T> curr;

    for (unsigned y = 1; y < lines.size() - 1; y++) {
        for (unsigned x = 1; x < lines[y].size() - 1; x++) {
            if (lines[y][x] == '9') {
                insert_func(curr[{ x, y }], { x, y });
            }
        }
    }

    for (char c = '8'; c >= '0'; c--) {
        prev.swap(curr);
        curr.clear();

        for (unsigned y = 1; y < lines.size() - 1; y++) {
            for (unsigned x = 1; x < lines[y].size() - 1; x++) {
                if (lines[y][x] == c) {
                    accum_func(curr[{ x, y }], prev[{ x + 1, y }]);
                    accum_func(curr[{ x, y }], prev[{ x - 1, y }]);
                    accum_func(curr[{ x, y }], prev[{ x, y + 1 }]);
                    accum_func(curr[{ x, y }], prev[{ x, y - 1 }]);
                }
            }
        }
    }

    auto count = std::accumulate(curr.begin(), curr.end(), std::size_t {}, [&](auto sum, auto& p) { return sum + extract_func(p.second); });
    return count;
}

std::string part1(std::istream& input)
{
    std::vector<std::string> lines = extend(read_lines(input));
    auto count = count_paths<std::set<Point>>(lines, [](std::set<Point>& m, Point p) { m.insert(p); }, [](auto& a, auto& b) { return a.insert(b.begin(), b.end()); }, [](auto& p) { return p.size(); });
    return std::to_string(count);
}

std::string part2(std::istream& input)
{
    std::vector<std::string> lines = extend(read_lines(input));
    auto count = count_paths<std::size_t>(lines, [](std::size_t& m, Point) { m = 1; }, [](auto& a, auto& b) { return a += b; }, [](auto& p) { return p; });
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
