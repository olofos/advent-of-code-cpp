#include <algorithm>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day13 {
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

struct Entry {
    int64_t ax, ay, bx, by, px, py;
};

std::optional<Entry> parse_entry(std::istream& input)
{
    int64_t ax, ay, bx, by, px, py;
    if (!expect(input, "Button")) {
        return std::nullopt;
    }
    expect(input, "A:");
    expect(input, "X+");
    input >> ax;
    expect(input, ",");
    expect(input, "Y+");
    input >> ay;
    expect(input, "Button");
    expect(input, "B:");
    expect(input, "X+");
    input >> bx;
    expect(input, ",");
    expect(input, "Y+");
    input >> by;
    expect(input, "Prize:");
    expect(input, "X=");
    input >> px;
    expect(input, ",");
    expect(input, "Y=");
    if (input >> py) {
        return Entry { ax, ay, bx, by, px, py };
    }
    return std::nullopt;
}

std::vector<Entry> parse(std::istream& input)
{
    std::vector<Entry> result;
    while (auto entry = parse_entry(input)) {
        result.push_back(*entry);
    }
    return result;
}

int64_t calculate_score(const std::vector<Entry>& entries)
{
    int64_t sum = 0;
    for (auto [ax, ay, bx, by, px, py] : entries) {
        auto det = ax * by - bx * ay;
        if (det == 0) {
            throw std::runtime_error("Unsolvable system: " + std::to_string(ax) + ", " + std::to_string(ay) + ", " + std::to_string(bx) + ", " + std::to_string(by) + ", " + std::to_string(px) + ", " + std::to_string(py));
        }
        auto nx = px * by - py * bx;
        auto ny = ax * py - ay * px;

        if (nx % det == 0 && ny % det == 0) {
            auto a = nx / det;
            auto b = ny / det;

            if (a >= 0 && b >= 0) {
                sum += 3 * a + b;
            }
        }
    }
    return sum;
}

std::string part1(std::istream& input)
{
    auto entries = parse(input);
    auto sum = calculate_score(entries);
    return std::to_string(sum);
}

std::string part2(std::istream& input)
{
    auto entries = parse(input);
    for (auto& entry : entries) {
        entry.px += 10000000000000;
        entry.py += 10000000000000;
    }
    auto sum = calculate_score(entries);
    return std::to_string(sum);
}
}

DayDescription Day13::description()
{
    DayDescription description { 13, 2024 };
    description.part1 = day13::part1;
    description.part2 = day13::part2;
    description.part1_test_result = "480";
    description.part2_test_result = "875318608908";
    description.test_input = "Button A: X+94, Y+34\nButton B: X+22, Y+67\nPrize: X=8400, Y=5400\n\nButton A: X+26, Y+66\nButton B: X+67, Y+21\nPrize: X=12748, Y=12176\n\nButton A: X+17, Y+86\nButton B: X+84, Y+37\nPrize: X=7870, Y=6450\n\nButton A: X+69, Y+23\nButton B: X+27, Y+71\nPrize: X=18641, Y=10279";
    return description;
}
