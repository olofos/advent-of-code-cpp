#pragma once
#ifndef AOC_DAY_H
#define AOC_DAY_H

#include <iostream>
#include <memory>
#include <optional>
#include <string>

class Day {
public:
    struct TestResult {
        std::string message;
        bool success;
    };

    TestResult test();
    std::string run();

public:
    virtual std::string part1(std::istream& input) = 0;
    virtual std::string part2(std::istream& input) = 0;
    virtual int day() = 0;
    virtual int year() = 0;

    virtual std::optional<std::string> part1_test_result() { return std::nullopt; };
    virtual std::optional<std::string> part2_test_result() { return std::nullopt; };
    virtual std::optional<std::string> test_input() { return std::nullopt; };

    Day() = default;
    virtual ~Day() = default;
    Day(const Day&) = delete;
    Day(Day&&) = default;
    Day& operator=(const Day&) = delete;
    Day& operator=(Day&&) = default;
};

bool run_all(const std::vector<std::unique_ptr<Day>>& days);

#endif
