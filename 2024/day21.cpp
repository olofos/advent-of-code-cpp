#include <algorithm>
#include <iostream>
#include <istream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "days.h"
#include "util.h"

namespace day21 {
using aoc::Point;
std::vector<std::string> parse(std::istream& input)
{
    std::string line;
    std::vector<std::string> lines;
    while (getline(input, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::string generate_sequence(const std::map<char, Point>& positions, Point forbidden, std::string_view line)
{
    Point curr = positions.find('A')->second;
    std::string result;

    for (char c : line) {
        std::vector<std::string> next_results;
        auto goal = positions.find(c)->second;
        if (Point { goal.x, curr.y } != forbidden) {
            result += std::string(std::abs(curr.x - goal.x), curr.x > goal.x ? '<' : '>');
            result += std::string(std::abs(curr.y - goal.y), curr.y > goal.y ? '^' : 'v');
        } else {
            result += std::string(std::abs(curr.y - goal.y), curr.y > goal.y ? '^' : 'v');
            result += std::string(std::abs(curr.x - goal.x), curr.x > goal.x ? '<' : '>');
        }
        result += 'A';
        curr = goal;
    }
    return result;
}

size_t get_complexity_sum(const std::vector<std::string>& lines, int steps)
{
    std::map<char, Point> numpad_positions = {
        { '7', { 0, 0 } },
        { '8', { 1, 0 } },
        { '9', { 2, 0 } },
        { '4', { 0, 1 } },
        { '5', { 1, 1 } },
        { '6', { 2, 1 } },
        { '1', { 0, 2 } },
        { '2', { 1, 2 } },
        { '3', { 2, 2 } },
        { '0', { 1, 3 } },
        { 'A', { 2, 3 } },
    };

    std::map<char, Point> dirpad_positions = {
        { '^', { 1, 0 } },
        { 'A', { 2, 0 } },
        { '<', { 0, 1 } },
        { 'v', { 1, 1 } },
        { '>', { 2, 1 } },
    };

    size_t sum = 0;
    for (auto& line : lines) {
        auto seq = generate_sequence(numpad_positions, Point { 0, 3 }, line);
        for (int n = 0; n < steps; n++) {
            seq = generate_sequence(dirpad_positions, Point { 0, 0 }, seq);
        }
        size_t complexity = std::stoi(line, nullptr, 10);

        sum += complexity * seq.size();
    }
    return sum;
}

std::string part1(std::istream& input)
{
    auto lines = parse(input);
    auto sum = get_complexity_sum(lines, 2);
    return std::to_string(sum);
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day21::description()
{
    DayDescription description { 21, 2024 };
    description.part1 = day21::part1;
    description.part2 = day21::part2;
    description.part1_test_result = "126384";
    // description.part2_test_result = "";
    description.test_input = "029A\n980A\n179A\n456A\n379A";
    return description;
}
