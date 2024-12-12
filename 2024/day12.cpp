#include <algorithm>
#include <array>
#include <iostream>
#include <istream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"
#include "util.h"

namespace day12 {
using aoc::Point;

uint64_t flood_fill(std::vector<std::string>& lines, aoc::Point start)
{
    std::queue<Point> queue;
    std::set<Point> region;
    queue.push(start);
    char region_name = lines[start.y][start.x];
    uint64_t area = 0;
    uint64_t circum = 0;
    while (!queue.empty()) {
        auto point = queue.front();
        queue.pop();
        if (lines[point.y][point.x] != region_name) {
            continue;
        }
        region.insert(point);
        std::array<Point, 4> offsets = { { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } } };
        int neighbors = 0;
        for (auto& offset : offsets) {
            auto p = point + offset;
            if (region.contains(p)) {
                neighbors++;
            }
            queue.push(p);
        }
        circum += 4 - 2 * neighbors;
        area++;
        lines[point.y][point.x] = '.';
    }
    return area * circum;
}

std::string part1(std::istream& input)
{
    std::vector<std::string> lines = aoc::read_lines_with_border(input);

    uint64_t score = 0;
    for (unsigned y = 1; y < lines.size() - 1; y++) {
        for (unsigned x = 1; x < lines[y].size() - 1; x++) {
            if (lines[y][x] != '.') {
                score += flood_fill(lines, { x, y });
            }
        }
    }

    return std::to_string(score);
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day12::description()
{
    DayDescription description { 12, 2024 };
    description.part1 = day12::part1;
    description.part2 = day12::part2;
    description.part1_test_result = "1930";
    // description.part2_test_result = "";
    description.test_input = "RRRRIICCFF\nRRRRIICCCF\nVVRRRCCFFF\nVVRCCCJFFF\nVVVVCJJCFE\nVVIVCCJJEE\nVVIIICJJEE\nMIIIIIJJEE\nMIIISIJEEE\nMMMISSJEEE";
    return description;
}
