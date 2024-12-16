#include <algorithm>
#include <iostream>
#include <istream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"
#include "util.h"

namespace day16 {
using aoc::Point;

enum class Dir {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct Node {
    Point position;
    Dir direction;

    auto operator<=>(const Node& other) const = default;
};

Dir turn_right(Dir dir)
{
    switch (dir) {
    case Dir::UP:
        return Dir::RIGHT;
    case Dir::RIGHT:
        return Dir::DOWN;
    case Dir::DOWN:
        return Dir::LEFT;
    case Dir::LEFT:
        return Dir::UP;
    }
    throw std::runtime_error("invalid direction");
}

Dir turn_left(Dir dir)
{
    switch (dir) {
    case Dir::UP:
        return Dir::LEFT;
    case Dir::RIGHT:
        return Dir::UP;
    case Dir::DOWN:
        return Dir::RIGHT;
    case Dir::LEFT:
        return Dir::DOWN;
    }
    throw std::runtime_error("invalid direction");
}

Point operator+(const Point& lhs, Dir dir)
{
    switch (dir) {
    case Dir::UP:
        return { lhs.x, lhs.y - 1 };
    case Dir::RIGHT:
        return { lhs.x + 1, lhs.y };
    case Dir::DOWN:
        return { lhs.x, lhs.y + 1 };
    case Dir::LEFT:
        return { lhs.x - 1, lhs.y };
    }
    throw std::runtime_error("invalid direction");
}

class Grid {
public:
    std::vector<char> values;
    unsigned width;
    unsigned height;

    char operator()(int x, int y) const { return values[y * width + x]; }
    char operator()(Point p) const { return (*this)(p.x, p.y); }

    char& operator()(int x, int y) { return values[y * width + x]; }
    char& operator()(Point p) { return (*this)(p.x, p.y); }

    Point find(char c) const
    {
        for (unsigned y = 0; y < height; y++) {
            for (unsigned x = 0; x < width; x++) {
                if ((*this)(x, y) == c) {
                    return Point { x, y };
                }
            }
        }
        throw std::runtime_error("could not find " + std::to_string(c));
    }
};

Grid parse_grid(std::istream& input)
{
    Grid grid;
    std::string line;
    while (std::getline(input, line)) {
        grid.values.insert(grid.values.end(), line.begin(), line.end());
    }
    grid.width = static_cast<unsigned>(line.size());
    grid.height = static_cast<unsigned>(grid.values.size() / grid.width);
    return grid;
}

std::string part1(std::istream& input)
{
    auto grid = parse_grid(input);
    auto start_pos = grid.find('S');
    auto end = grid.find('E');

    auto cmp = [](const std::pair<Node, unsigned>& lhs, const std::pair<Node, unsigned>& rhs) { return lhs.second > rhs.second; };
    std::priority_queue<std::pair<Node, unsigned>, std::vector<std::pair<Node, unsigned>>, decltype(cmp)> queue(cmp);

    queue.push({ { start_pos, Dir::RIGHT }, 0 });

    std::set<Node> visited;

    while (!queue.empty()) {
        auto [node, score] = queue.top();
        queue.pop();
        if (visited.contains(node)) {
            continue;
        }
        visited.insert(node);
        if (node.position == end) {
            return std::to_string(score);
        }
        std::pair<Node, unsigned> neighbors[3] = {
            { { node.position + node.direction, node.direction }, score + 1 },
            { { node.position + turn_left(node.direction), turn_left(node.direction) }, score + 1001 },
            { { node.position + turn_right(node.direction), turn_right(node.direction) }, score + 1001 },
        };
        for (auto& neighbor : neighbors) {
            if (grid(neighbor.first.position) != '#') {
                queue.push(neighbor);
            }
        }
    }
    throw std::runtime_error("no path found");
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day16::description()
{
    DayDescription description { 16, 2024 };
    description.part1 = day16::part1;
    description.part2 = day16::part2;
    description.part1_test_result = "7036";
    // description.part2_test_result = "";
    description.test_input = "###############\n#.......#....E#\n#.#.###.#.###.#\n#.....#.#...#.#\n#.###.#####.#.#\n#.#.#.......#.#\n#.#.#####.###.#\n#...........#.#\n###.#.#####.#.#\n#...#.....#.#.#\n#.#.#.###.#.#.#\n#.....#...#.#.#\n#.###.#.#.#.#.#\n#S..#.....#...#\n###############";
    return description;
}
