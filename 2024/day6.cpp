#include <algorithm>
#include <iostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day6 {

struct Dir {
    int x;
    int y;

    Dir turn_right() { return { -y, x }; }

    uint8_t index()
    {
        if (x == 1 && y == 0) {
            return 1;
        } else if (x == 0 && y == 1) {
            return 2;
        } else if (x == -1 && y == 0) {
            return 4;
        } else {
            return 8;
        }
    }
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

    bool is_inside(const Point& point)
    {
        return point.x >= 0 && point.x < width && point.y >= 0 && point.y < height;
    }

    bool is_obstacle(const Point& point) { return obstacles.find(point) != obstacles.end(); }

    bool step()
    {
        if (is_obstacle(guard + dir)) {
            dir = dir.turn_right();
        } else {
            guard += dir;
        }

        return is_inside(guard);
    }
};

bool has_loop(Map& map, std::map<Point, uint8_t> visited, Point obstacle)
{
    if (!map.is_inside(obstacle) || visited[obstacle] != 0 || map.is_obstacle(obstacle)) {
        return false;
    }
    Point old_guard = map.guard;
    Dir old_dir = map.dir;
    map.obstacles.insert(obstacle);

    bool found_loop = false;

    while (map.step()) {
        if (visited[map.guard] & map.dir.index()) {
            found_loop = true;
            break;
        }
        visited[map.guard] |= map.dir.index();
    }

    map.obstacles.erase(obstacle);
    map.dir = old_dir;
    map.guard = old_guard;

    return found_loop;
}

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

std::string part1(std::istream& input)
{
    Map map = parse(input);
    std::set<Point> visited = { map.guard };

    while (map.step()) {
        visited.insert(map.guard);
    }

    return std::to_string(visited.size());
}

std::string part2(std::istream& input)
{
    Map map = parse(input);
    std::map<Point, uint8_t> visited = { { map.guard, map.dir.index() } };
    std::set<Point> loop_obstacles;

    while (map.step()) {
        visited[map.guard] |= map.dir.index();

        auto next = map.guard + map.dir;
        if (loop_obstacles.find(next) == loop_obstacles.end() && has_loop(map, visited, next)) {
            loop_obstacles.insert(next);
        }
    }

    return std::to_string(loop_obstacles.size());
}
}

DayDescription Day6::description()
{
    DayDescription description { 6, 2024 };
    description.part1 = day6::part1;
    description.part2 = day6::part2;
    description.part1_test_result = "41";
    description.part2_test_result = "6";
    description.test_input = "....#.....\n.........#\n..........\n..#.......\n.......#..\n..........\n.#..^.....\n........#.\n#.........\n......#...\n";
    return description;
}
