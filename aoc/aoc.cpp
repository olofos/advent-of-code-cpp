#include <chrono>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "aoc.h"

namespace {
struct TestResult {
    std::string message;
    bool success;
};

TestResult operator+(const TestResult& lhs, const TestResult& rhs)
{
    return { lhs.message + rhs.message, lhs.success && rhs.success };
}

TestResult run_test(PartFunc func, const std::optional<std::string>& test_result, const std::string& test_input, int part)
{
    std::ostringstream output;
    bool success = true;
    if (test_result.has_value()) {
        std::stringstream input(test_input);
        try {
            auto result = func(input);
            if (result == test_result.value()) {
                output << "Part " << part << " passed\n";
            } else {
                output << "Part " << part << " failed: Expected " << test_result.value() << ", got " << result << "\n";
                success = false;
            }
        } catch (const std::exception& e) {
            output << "Part " << part << " failed: " << e.what() << "\n";
            success = false;
        }
    } else {
        output << "No test result for part " << part << "\n";
    }

    return { output.str(), success };
}

TestResult run_tests(const DayDescription& description)
{
    if (!description.test_input.has_value()) {
        return { "No test input for day " + std::to_string(description.day) + "\n", true };
    }

    auto result1 = run_test(description.part1, description.part1_test_result, description.test_input.value(), 1);
    auto result2 = run_test(description.part2, description.part2_test_result, description.test_input.value(), 2);

    return TestResult { "Running tests for day " + std::to_string(description.day) + " for year " + "\n", true } + result1 + result2;
}

std::string run_part(PartFunc func, std::istream& input)
{
    std::ostringstream output;

    if (!func) {
        return "Not implemented";
    }

    try {
        auto start = std::chrono::high_resolution_clock::now();
        auto result = func(input);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - start);
        output << std::format("{:>15} {:7.2f}ms ", result, duration.count());
    } catch (const std::exception& e) {
        output << "Error: " << e.what();
    }

    return output.str();
}

std::string run_day(DayDescription& description)
{
    std::ostringstream output;

    output << "Day " << description.day << ": ";
    std::string filename = "data/" + std::to_string(description.year) + "/day" + std::to_string(description.day) + ".dat";
    std::ifstream input(filename, std::ios::in);

    if (!input.is_open()) {
        output << "Could not open file " << filename << "\n";
        return output.str();
    }

    output << run_part(description.part1, input);
    output << "   ";

    input.clear();
    input.seekg(0, std::ios::beg);

    output << run_part(description.part2, input);
    output << "\n";

    return output.str();
}
}

int aoc::run_all(const std::vector<std::unique_ptr<Day>>& days)
{
    const int SUCCESS = 0;
    const int FAILURE = 1;

    int failures = 0;
    std::string messages;

    std::vector<DayDescription> descriptions;
    for (auto& day : days) {
        descriptions.emplace_back(day->description());
    }

    int year = descriptions[0].year;
    std::set<int> day_set;

    for (auto& description : descriptions) {
        if (description.year != year) {
            std::cout << "Days must be in same year\n";
            return FAILURE;
        }
        if (day_set.find(description.day) != day_set.end()) {
            std::cout << "Day " << description.day << " is not unique\n";
            return FAILURE;
        }
        day_set.insert(description.day);
    }

    for (auto& description : descriptions) {
        TestResult result = run_tests(description);
        messages += result.message;
        if (!result.success) {
            failures++;
        }
    }

    if (failures > 0) {
        std::cout << messages << "\n";
        std::cout << failures << " tests failed\n";
        return FAILURE;
    }

    std::cout << "All tests passed\n\n";

    for (auto& description : descriptions) {
        std::cout << run_day(description);
    }

    return SUCCESS;
}
