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

class SmallestStringSet {
    std::vector<std::string> strings;

public:
    SmallestStringSet() { }
    SmallestStringSet(const std::string& str)
        : strings({ str })
    {
    }
    void add(const std::string& str)
    {
        if (strings.empty() || str.size() < strings.back().size()) {
            strings = { str };
        } else if (str.size() == strings.back().size()) {
            strings.push_back(str);
        }
    }

    auto begin() const { return strings.begin(); }
    auto end() const { return strings.end(); }
    auto size() const { return strings.back().size(); }
};

void generate_sequence(const std::map<char, Point>& positions, Point forbidden, std::string_view line, SmallestStringSet& smallest_set)
{
    std::vector<std::string> curr_results = { "" };
    Point curr = positions.find('A')->second;

    for (char c : line) {
        std::vector<std::string> next_results;
        auto goal = positions.find(c)->second;

        if (curr.x == goal.x) {
            std::string ds;
            if (curr.y > goal.y) {
                ds = std::string(curr.y - goal.y, '^');
            } else {
                ds = std::string(goal.y - curr.y, 'v');
            }

            for (auto& s : curr_results) {
                next_results.push_back(s + ds);
            }
        } else if (curr.y == goal.y) {
            std::string ds;
            if (curr.x > goal.x) {
                ds = std::string(curr.x - goal.x, '<');
            } else {
                ds = std::string(goal.x - curr.x, '>');
            }

            for (auto& s : curr_results) {
                next_results.push_back(s + ds);
            }
        } else {
            Point corner1 = { curr.x, goal.y };
            Point corner2 = { goal.x, curr.y };

            if (forbidden != corner2) {
                std::string ds;
                if (curr.x > goal.x) {
                    ds += std::string(curr.x - goal.x, '<');
                } else {
                    ds += std::string(goal.x - curr.x, '>');
                }
                if (curr.y > goal.y) {
                    ds += std::string(curr.y - goal.y, '^');
                } else {
                    ds += std::string(goal.y - curr.y, 'v');
                }
                for (auto& s : curr_results) {
                    next_results.push_back(s + ds);
                }
            }

            if (forbidden != corner1) {
                std::string ds;
                if (curr.y > goal.y) {
                    ds += std::string(curr.y - goal.y, '^');
                } else {
                    ds += std::string(goal.y - curr.y, 'v');
                }
                if (curr.x > goal.x) {
                    ds += std::string(curr.x - goal.x, '<');
                } else {
                    ds += std::string(goal.x - curr.x, '>');
                }
                for (auto& s : curr_results) {
                    next_results.push_back(s + ds);
                }
            }
        }
        for (auto& s : next_results) {
            s += 'A';
        }
        curr = goal;
        curr_results = next_results;
    }

    for (auto s : curr_results) {
        smallest_set.add(s);
    }
}

SmallestStringSet generate_sequence(const std::map<char, Point>& positions, Point forbidden, const SmallestStringSet& lines)
{
    SmallestStringSet result;
    for (auto& line : lines) {
        generate_sequence(positions, forbidden, line, result);
    }
    return result;
}

std::string part1(std::istream& input)
{
    auto lines = parse(input);

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
        auto seq1 = generate_sequence(numpad_positions, Point { 0, 3 }, line);
        auto seq2 = generate_sequence(dirpad_positions, Point { 0, 0 }, seq1);
        auto seq3 = generate_sequence(dirpad_positions, Point { 0, 0 }, seq2);
        size_t complexity = std::stoi(line, nullptr, 10);

        sum += complexity * seq3.size();
    }
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
