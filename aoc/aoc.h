#pragma once
#ifndef AOC_DAY_H
#define AOC_DAY_H

#include <iostream>
#include <memory>
#include <optional>
#include <string>

typedef std::string (*PartFunc)(std::istream& input);

struct DayDescription {
    int day;
    int year;
    std::optional<std::string> test_input = std::nullopt;
    std::optional<std::string> part1_test_result = std::nullopt;
    std::optional<std::string> part2_test_result = std::nullopt;
    bool is_slow = false;

    PartFunc part1 = 0;
    PartFunc part2 = 0;
};

class Day {
public:
    virtual DayDescription description() = 0;

    Day() = default;
    virtual ~Day() = default;
    Day(const Day&) = delete;
    Day(Day&&) = default;
    Day& operator=(const Day&) = delete;
    Day& operator=(Day&&) = default;
};

namespace aoc {
int run_all(const std::vector<std::unique_ptr<Day>>& days);

template <typename... Ds>
int run_all()
{
    std::unique_ptr<Day> init[] { std::make_unique<Ds>()... };
    return run_all(std::vector<std::unique_ptr<Day>> { std::make_move_iterator(std::begin(init)), std::make_move_iterator(std::end(init)) });
}
}

#endif
