#include <algorithm>
#include <array>
#include <iostream>
#include <istream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"
#include "util.h"

namespace day14 {
using aoc::Point;

bool expect(std::istream& input, std::string_view expected)
{
    auto old_width = input.width();
    input.width(expected.size());
    std::string actual;
    if (input >> actual) {
        input.width(old_width);
        if (actual != expected) {
            throw std::runtime_error("Parse error. Expected '" + std::string(expected) + "' but got '" + actual + "'");
        }
        return true;
    } else {
        return false;
    }
}

struct Robot {
    Point position;
    Point velocity;
};

std::istream& operator>>(std::istream& input, Robot& robot)
{
    expect(input, "p=");
    input >> robot.position.x;
    expect(input, ",");
    input >> robot.position.y;
    expect(input, "v=");
    input >> robot.velocity.x;
    expect(input, ",");
    input >> robot.velocity.y;
    return input;
}

std::vector<Robot> parse(std::istream& input)
{
    std::vector<Robot> result;
    Robot r;
    while (input >> r) {
        result.push_back(r);
    }
    return result;
}

std::string part1(std::istream& input)
{
    auto robots = parse(input);

    int width = 101, height = 103;
    if (robots.size() == 12) {
        width = 11;
        height = 7;
    }

    for (auto& r : robots) {
        auto pt = r.position + 100 * r.velocity;
        r.position = {
            (pt.x % width + width) % width,
            (pt.y % height + height) % height
        };
    }

    std::array<int, 4> counts = { 0, 0, 0, 0 };
    for (auto& r : robots) {
        if (r.position.x == (width - 1) / 2 || r.position.y == (height - 1) / 2) {
            continue;
        }
        int quadrant = 0;
        if (r.position.x > (width - 1) / 2) {
            quadrant |= 1;
        }
        if (r.position.y > (height - 1) / 2) {
            quadrant |= 2;
        }
        counts[quadrant]++;
    }

    auto score = counts[0] * counts[1] * counts[2] * counts[3];
    return std::to_string(score);
}

void print_map(const std::vector<Robot>& robots, int width, int height)
{
    std::map<Point, int> points;
    for (auto& r : robots) {
        points[r.position]++;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (points.find({ x, y }) == points.end()) {
                std::cout << ".";
            } else {
                std::cout << points[{ x, y }];
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::string part2(std::istream& input)
{
    auto robots = parse(input);

    int width = 101, height = 103;
    unsigned step;

    for (step = 0; step < 10000; step++) {
        std::vector<std::vector<int>> entries(height);

        for (auto& r : robots) {
            auto pt = r.position + r.velocity;
            r.position = {
                (pt.x % width + width) % width,
                (pt.y % height + height) % height
            };
            entries[r.position.y].push_back(r.position.x);
        }

        int max_count = 0;
        for (auto& line : entries) {
            if (line.size() < 2) {
                continue;
            }
            std::sort(line.begin(), line.end());
            auto end = std::unique(line.begin(), line.end());
            int max_line_count = 0;
            int line_count = 0;
            for (auto it = line.begin(); it != end - 1; ++it) {
                if (*(it + 1) - *it == 1) {
                    line_count++;
                    max_line_count = std::max(line_count, max_line_count);
                } else {
                    line_count = 0;
                }
            }
            max_count = std::max(max_line_count, max_count);
        }

        if (max_count > 8) {
            print_map(robots, width, height);
            return std::to_string(step);
        }
    }
    return "no tree found";
}
}

DayDescription Day14::description()
{
    DayDescription description { 14, 2024 };
    description.part1 = day14::part1;
    description.part2 = day14::part2;
    description.part1_test_result = "12";
    // description.part2_test_result = "";
    description.test_input = "p=0,4 v=3,-3\np=6,3 v=-1,-3\np=10,3 v=-1,2\np=2,0 v=2,-1\np=0,0 v=1,3\np=3,0 v=-2,-2\np=7,6 v=-1,-3\np=3,0 v=-1,-2\np=9,3 v=2,3\np=7,3 v=-1,2\np=2,4 v=2,-3\np=9,5 v=-3,-3";
    return description;
}
