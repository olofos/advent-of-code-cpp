#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <ranges>
#include <set>
#include <string>
#include <vector>

#include "days.h"
#include "util.h"

namespace day8 {

using aoc::Point;

std::tuple<std::map<char, std::vector<Point>>, std::size_t, std::size_t> parse(std::istream& input)
{
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    std::map<char, std::vector<Point>> map;

    for (unsigned y = 0; y < lines.size(); y++) {
        for (unsigned x = 0; x < lines[y].size(); x++) {
            if (lines[y][x] != '.') {
                map[lines[y][x]].push_back({ x, y });
            }
        }
    }

    return { map, lines[0].size(), lines.size() };
}

bool is_inside(const Point& point, std::size_t width, std::size_t height)
{
    return point.x >= 0 && point.x < static_cast<int>(width) && point.y >= 0 && point.y < static_cast<int>(height);
}

std::string part1(std::istream& input)
{
    auto [map, width, height] = parse(input);

    std::set<Point> antinodes;

    for (auto& points : std::views::values(map)) {
        for (unsigned i = 0; i < points.size(); i++) {
            for (unsigned j = i + 1; j < points.size(); j++) {
                if (is_inside(2 * points[i] - points[j], width, height)) {
                    antinodes.insert(2 * points[i] - points[j]);
                }
                if (is_inside(2 * points[j] - points[i], width, height)) {
                    antinodes.insert(2 * points[j] - points[i]);
                }
            }
        }
    }

    return std::to_string(antinodes.size());
}

std::string part2(std::istream& input)
{
    auto [map, width, height] = parse(input);

    std::set<Point> antinodes;

    for (auto& points : std::views::values(map)) {
        for (unsigned i = 0; i < points.size(); i++) {
            for (unsigned j = i + 1; j < points.size(); j++) {
                if (std::gcd(points[i].x - points[j].x, points[i].y - points[j].y) != 1) {
                    throw std::runtime_error("this code assumes that the coordinates are coprime");
                }
                for (Point pt = points[i] - (points[i] - points[j]); is_inside(pt, width, height); pt += points[i] - points[j]) {
                    antinodes.insert(pt);
                }
                for (Point pt = points[j] - (points[j] - points[i]); is_inside(pt, width, height); pt += points[j] - points[i]) {
                    antinodes.insert(pt);
                }
            }
        }
    }

    return std::to_string(antinodes.size());
}
}

DayDescription Day8::description()
{
    DayDescription description { 8, 2024 };
    description.part1 = day8::part1;
    description.part2 = day8::part2;
    description.part1_test_result = "14";
    description.part2_test_result = "34";
    description.test_input = "............\n........0...\n.....0......\n.......0....\n....0.......\n......A.....\n............\n............\n........A...\n.........A..\n............\n............\n";
    return description;
}
