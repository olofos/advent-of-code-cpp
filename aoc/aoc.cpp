#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "day.h"

Day::TestResult Day::test()
{
    std::ostringstream output;

    if (!test_input().has_value()) {
        output << "No test input for day " << day() << "\n";
        return { output.str(), true };
    }

    bool success = true;

    output << "Running tests for day " << day() << "\n";
    if (part1_test_result().has_value()) {
        std::stringstream input(test_input().value());
        try {
            auto result = part1(input);
            if (result == part1_test_result().value()) {
                output << "Part 1 passed\n";
            } else {
                output << "Part 1 failed: Expected " << part1_test_result().value() << ", got " << result << "\n";
                success = false;
            }
        } catch (const std::exception& e) {
            output << "Part 1 failed: " << e.what() << "\n";
            success = false;
        }
    } else {
        output << "No test result for part 1\n";
    }

    if (part2_test_result().has_value()) {
        std::stringstream input(test_input().value());
        try {
            auto result = part2(input);
            if (result == part2_test_result().value()) {
                output << "Part 2 passed\n";
            } else {
                output << "Part 2 failed: Expected " << part2_test_result().value() << ", got " << result << "\n";
                success = false;
            }
        } catch (const std::exception& e) {
            output << "Part 2 failed: " << e.what() << "\n";
            success = false;
        }
    } else {
        output << "No test result for part 2\n";
    }

    return { output.str(), success };
}

std::string Day::run()
{
    std::ostringstream output;

    output << "Day " << day() << ": ";
    std::string filename = "data/" + std::to_string(year()) + "/day" + std::to_string(day()) + ".dat";
    std::ifstream input(filename, std::ios::in);

    if (!input.is_open()) {
        output << "Could not open file " << filename << "\n";
        return output.str();
    }

    try {
        auto result = part1(input);
        output << std::setw(12) << result;
    } catch (const std::exception& e) {
        output << "Error: " << e.what();
    }

    output << "   ";

    input.clear();
    input.seekg(0, std::ios::beg);

    try {
        auto result = part2(input);
        output << std::setw(12) << result;
    } catch (const std::exception& e) {
        output << "Error: " << e.what();
    }
    output << "\n";

    return output.str();
}

bool run_all(const std::vector<std::unique_ptr<Day>>& days)
{
    int failures = 0;
    std::string messages;
    for (auto& day : days) {
        Day::TestResult result = day->test();
        messages += result.message;
        if (!result.success) {
            failures++;
        }
    }
    if (failures > 0) {
        std::cout << messages << "\n";
        std::cout << failures << " tests failed\n";
        return false;
    }

    std::cout << "All tests passed\n\n";
    for (auto& day : days) {
        std::cout << day->run();
    }

    return true;
}
