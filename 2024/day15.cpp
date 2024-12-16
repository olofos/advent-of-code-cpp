#include <algorithm>
#include <iostream>
#include <istream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"
#include "util.h"

namespace day15 {
using aoc::Point;

class Grid {
public:
    std::vector<char> values;
    unsigned width;
    unsigned height;

    char operator()(int x, int y) const { return values[y * width + x]; }
    char operator()(Point p) const { return (*this)(p.x, p.y); }

    char& operator()(int x, int y) { return values[y * width + x]; }
    char& operator()(Point p) { return (*this)(p.x, p.y); }

    std::optional<Point> find(char c) const
    {
        for (unsigned y = 0; y < height; y++) {
            for (unsigned x = 0; x < width; x++) {
                if ((*this)(x, y) == c) {
                    return Point { x, y };
                }
            }
        }
        return std::nullopt;
    }
};

Grid parse_grid(std::istream& input)
{
    Grid grid;
    std::string line;
    while (std::getline(input, line)) {
        if (line == "") {
            break;
        }
        grid.values.insert(grid.values.end(), line.begin(), line.end());
        grid.width = static_cast<unsigned>(line.size());
    }
    grid.height = static_cast<unsigned>(grid.values.size() / grid.width);
    return grid;
}

std::vector<Point> parse_path(std::istream& input)
{
    std::vector<Point> path;
    char c;
    while (input >> c) {
        switch (c) {
        case '^':
            path.push_back({ 0, -1 });
            break;
        case '>':
            path.push_back({ 1, 0 });
            break;
        case '<':
            path.push_back({ -1, 0 });
            break;
        case 'v':
            path.push_back({ 0, 1 });
            break;
        case '\n':
            break;
        default:
            throw std::runtime_error("invalid direction " + std::string(1, c));
        }
    }
    return path;
}

std::string part1(std::istream& input)
{
    auto grid = parse_grid(input);
    auto path = parse_path(input);
    auto robot_opt = grid.find('@');
    if (!robot_opt) {
        throw std::runtime_error("no robot");
    }
    auto robot = robot_opt.value();

    for (auto dir : path) {
        Point new_robot = robot + dir;
        Point new_box = robot + dir;
        bool floor_found = false;

        while (grid(new_box) == 'O') {
            new_box += dir;
        }

        if (grid(new_box) == '.') {
            grid(new_box) = 'O';
            grid(robot) = '.';
            grid(new_robot) = '@';
            robot = new_robot;
        }
    }

    int score = 0;
    for (unsigned y = 0; y < grid.height; y++) {
        for (unsigned x = 0; x < grid.width; x++) {
            if (grid(x, y) == 'O') {
                score += x + 100 * y;
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

DayDescription Day15::description()
{
    DayDescription description { 15, 2024 };
    description.part1 = day15::part1;
    description.part2 = day15::part2;
    description.part1_test_result = "10092";
    // description.part2_test_result = "";
    description.test_input = "##########\n#..O..O.O#\n#......O.#\n#.OO..O.O#\n#..O@..O.#\n#O#..O...#\n#O..O..O.#\n#.OO.O.OO#\n#....O...#\n##########\n\n<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^\nvvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v\n><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<\n<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^\n^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><\n^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^\n>^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^\n<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>\n^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>\nv^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^";
    return description;
}
