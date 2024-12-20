#include <algorithm>
#include <array>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"
#include "util.h"

namespace day20 {
using aoc::Point;
class Grid {
public:
    std::vector<int> values;
    unsigned width;
    unsigned height;

    int operator()(int x, int y) const { return values[y * width + x]; }
    int operator()(Point p) const { return (*this)(p.x, p.y); }

    int& operator()(int x, int y) { return values[y * width + x]; }
    int& operator()(Point p) { return (*this)(p.x, p.y); }

    Point find(int c) const
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

    bool is_inside(Point p) const
    {
        return p.x >= 0 && p.x < static_cast<int>(width) && p.y >= 0 && p.y < static_cast<int>(height);
    }

    bool is_not_wall(Point p) const
    {
        return is_inside(p) && (*this)(p) >= 0;
    }
};

std::tuple<Grid, Point, Point> parse(std::istream& input)
{
    Grid grid;
    char c;
    unsigned width = 0;
    unsigned height = 0;
    Point start, end;

    unsigned x = 0;

    while (input >> std::noskipws >> c) {
        if (c == '\n') {
            height++;
            x = 0;
            continue;
        } else if (c == '#') {
            grid.values.push_back(-1);
        } else {
            grid.values.push_back(std::numeric_limits<int>::max());
        }

        if (c == 'S') {
            start = Point { x, height };
        } else if (c == 'E') {
            end = Point { x, height };
        }

        x++;
    }
    grid.height = height;
    grid.width = static_cast<unsigned>(grid.values.size() / grid.height);
    return { grid, start, end };
}

std::vector<Point> fill_grid_and_find_path(Grid& grid, Point start, Point end)
{
    Point point = start;
    std::vector<Point> path = { start };
    grid(start) = 0;
    while (point != end) {
        const std::array<Point, 4> offsets = { { { 1, 0 }, { 0, 1 }, { 0, -1 }, { -1, 0 } } };
        Point prev_point = point;
        for (auto& offset : offsets) {
            auto p = point + offset;
            if (p.x < 0 || p.y < 0 || p.x >= static_cast<int>(grid.width) || p.y >= static_cast<int>(grid.height) || grid(p) < grid(point)) {
                continue;
            }
            grid(p) = grid(point) + 1;
            path.push_back(p);
            point = p;
            break;
        }
    }
    return path;
}

unsigned count_shortcuts(const Grid& grid, const std::vector<Point>& path, Point start, Point end, int max, int goal)
{
    unsigned count = 0;
    for (auto point : path) {
        for (int y = -max; y <= max; y++) {
            for (int x = -max; x <= max; x++) {
                auto p = point + Point { x, y };
                if (grid.is_not_wall(p) && std::abs(x) + std::abs(y) <= max && grid(point) - grid(p) - std::abs(x) - std::abs(y) >= goal) {
                    count++;
                }
            }
        }
    }

    return count;
}

std::string part1(std::istream& input)
{
    auto [grid, start, end] = parse(input);
    int max_shortcut = 2;
    auto count = count_shortcuts(grid, fill_grid_and_find_path(grid, start, end), start, end, 2, grid.width > 16 ? 100 : 10);
    return std::to_string(count);
}

std::string part2(std::istream& input)
{
    auto [grid, start, end] = parse(input);
    auto path = fill_grid_and_find_path(grid, start, end);
    auto count = count_shortcuts(grid, path, start, end, 20, grid.width > 16 ? 100 : 50);
    return std::to_string(count);
}
}

DayDescription Day20::description()
{
    DayDescription description { 20, 2024 };
    description.part1 = day20::part1;
    description.part2 = day20::part2;
    description.part1_test_result = "10";
    description.part2_test_result = "285";
    description.test_input = "###############\n#...#...#.....#\n#.#.#.#.#.###.#\n#S#...#.#.#...#\n#######.#.#.###\n#######.#.#...#\n#######.#.###.#\n###..E#...#...#\n###.#######.###\n#...###...#...#\n#.#####.#.###.#\n#.#...#.#.#...#\n#.#.#.#.#.#.###\n#...#...#...###\n###############\n";
    return description;
}
