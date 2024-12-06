#include <algorithm>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace {

struct Dir {
    int x;
    int y;

    Dir turn_right() { return { -y, x }; }
};

struct Point {
    int x;
    int y;

    Point operator+(const Dir& other) const { return { x + other.x, y + other.y }; }
    Point operator+=(const Dir& other) { return *this = *this + other; }

    auto operator<=>(const Point&) const = default;
};

struct Map {
    std::set<Point> obstacles;
    Point guard;
    Dir dir = { 0, -1 };
    int width;
    int height;

    bool is_inside()
    {
        return guard.x >= 0 && guard.x < width && guard.y >= 0 && guard.y < height;
    }

    bool step()
    {
        while (obstacles.find(guard + dir) != obstacles.end()) {
            dir = dir.turn_right();
        }
        guard += dir;

        return is_inside();
    }
};

Map parse(std::istream& input)
{
    std::string line;
    Map map;

    map.height = 0;
    for (int y = 0; std::getline(input, line); ++y, ++map.height) {
        map.width = static_cast<int>(line.size());
        for (int x = 0; x < static_cast<int>(line.size()); ++x) {
            if (line[x] == '#') {
                map.obstacles.insert({ x, y });
            } else if (line[x] == '^') {
                map.guard = { x, y };
            }
        }
    }

    return map;
}

}

std::string Day6::part1(std::istream& input)
{
    Map map = parse(input);
    std::set<Point> visited = { map.guard };

    while (map.step()) {
        visited.insert(map.guard);
    }

    return std::to_string(visited.size());
}

std::string Day6::part2(std::istream& input)
{
    Map map = parse(input);

    throw std::runtime_error("not implemented");
}