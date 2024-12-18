#include <algorithm>
#include <array>
#include <deque>
#include <format>
#include <iostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"
#include "util.h"

namespace day18 {
using aoc::Point;

std::vector<Point> parse(std::istream& input)
{
    std::vector<Point> points;
    Point pt;
    while (input >> pt.x) {
        input.ignore(1);
        input >> pt.y;
        points.push_back(pt);
    }
    return points;
}

std::string part1(std::istream& input)
{
    auto point_vec = parse(input);

    int width = 0, height = 0;
    for (auto& p : point_vec) {
        width = std::max(width, p.x + 1);
        height = std::max(height, p.y + 1);
    }

    int num_points = 1024;
    if (width == 7 && height == 7) {
        num_points = 12;
    }
    point_vec.resize(num_points);

    std::set<Point> points(point_vec.begin(), point_vec.end());

    std::deque<std::pair<Point, unsigned>> queue = { { { { 0, 0 }, 0 } } };
    std::set<Point> visited;

    while (!queue.empty()) {
        auto [point, dist] = queue.front();
        queue.pop_front();

        if (visited.contains(point)) {
            continue;
        }

        if (point == Point { width - 1, height - 1 }) {
            return std::to_string(dist);
        }

        visited.insert(point);

        std::array<Point, 4> offsets = { { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } } };
        for (auto& offset : offsets) {
            auto p = point + offset;
            if (p.x < 0 || p.y < 0 || p.x >= width || p.y >= height || points.find(p) != points.end() || visited.contains(p)) {
                continue;
            }
            queue.emplace_back(p, dist + 1);
        }
    }

    throw std::runtime_error("no path found");
}

std::optional<std::set<Point>> find_path(std::set<Point>& points, int width, int height)
{
    std::vector<Point> stack = { { 0, 0 } };
    std::map<Point, Point> visited;

    visited[Point { 0, 0 }] = Point { 0, 0 };

    while (!stack.empty()) {
        auto point = stack.back();

        if (point == Point { width - 1, height - 1 }) {
            std::set<Point> path = { { point } };
            while (point != Point { 0, 0 }) {
                auto it = visited.find(point);
                if (it == visited.end()) {
                    break;
                }
                path.insert(it->second);
                point = it->second;
            }
            return path;
        }

        stack.pop_back();

        std::array<Point, 4> offsets = { { { 1, 0 }, { 0, 1 }, { 0, -1 }, { -1, 0 } } };
        for (auto& offset : offsets) {
            auto p = point + offset;
            if (p.x < 0 || p.y < 0 || p.x >= width || p.y >= height || points.find(p) != points.end() || visited.contains(p)) {
                continue;
            }
            visited[p] = point;
            stack.push_back(p);
        }
    }

    return std::nullopt;
}

std::string part2(std::istream& input)
{
    auto point_vec = parse(input);

    int width = 0, height = 0;
    for (auto& p : point_vec) {
        width = std::max(width, p.x + 1);
        height = std::max(height, p.y + 1);
    }

    int num_points = 1024;
    if (width == 7 && height == 7) {
        num_points = 12;
    }

    std::set<Point> points;
    std::set<Point> path = find_path(points, width, height).value();

    for (auto& p : point_vec) {
        points.insert(p);
        if (path.contains(p)) {
            auto result = find_path(points, width, height);
            if (result.has_value()) {
                path = result.value();
            } else {
                return std::format("{},{}", p.x, p.y);
            }
        }
    }
    throw std::runtime_error("no result found");
}
}

DayDescription Day18::description()
{
    DayDescription description { 18, 2024 };
    description.part1 = day18::part1;
    description.part2 = day18::part2;
    description.part1_test_result = "22";
    description.part2_test_result = "6,1";
    description.test_input = "5,4\n4,2\n4,5\n3,0\n2,1\n6,3\n2,4\n1,5\n0,6\n3,3\n2,6\n5,1\n1,2\n5,5\n2,5\n6,5\n1,4\n0,4\n6,4\n1,1\n6,1\n1,0\n0,5\n1,6\n2,0";
    return description;
}
