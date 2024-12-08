#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <map>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace {

class Point {
public:
    int x;
    int y;

    Point(int x, int y)
        : x(x)
        , y(y)
    {
    }
    auto operator<=>(const Point&) const = default;
};

Point operator+(const Point& lhs, const Point& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }
Point operator-(const Point& lhs, const Point& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
Point operator*(const Point& lhs, int rhs) { return { lhs.x * rhs, lhs.y * rhs }; }
Point operator*(int lhs, const Point& rhs) { return { lhs * rhs.x, lhs * rhs.y }; }

std::vector<std::string> read_lines(std::istream& input)
{
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }
    return lines;
}

}

std::string Day8::part1(std::istream& input)
{
    auto lines = read_lines(input);

    std::map<char, std::vector<Point>> map;

    for (int y = 0; y < lines.size(); y++) {
        for (int x = 0; x < lines[y].size(); x++) {
            if (lines[y][x] != '.') {
                map[lines[y][x]].push_back({ x, y });
            }
        }
    }

    std::set<Point> antinodes;

    for (auto& points : std::views::values(map)) {
        for (unsigned i = 0; i < points.size(); i++) {
            for (unsigned j = i + 1; j < points.size(); j++) {
                antinodes.insert(2 * points[i] - points[j]);
                antinodes.insert(2 * points[j] - points[i]);
            }
        }
    }

    auto width = lines[0].size();
    auto height = lines.size();
    int count = 0;
    for (auto point : antinodes) {
        if (point.x >= 0 && point.x < width && point.y >= 0 && point.y < height) {
            count++;
        }
    }

    return std::to_string(count);
}

std::string Day8::part2(std::istream&)
{
    throw std::runtime_error("not implemented");
}
