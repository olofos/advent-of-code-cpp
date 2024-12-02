#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "day.h"

std::string Day::test()
{
    std::ostringstream output;

    if (!test_input().has_value()) {
        output << "No test input for day " << day() << "\n";
        return output.str();
    }

    output << "Running tests for day " << day() << "\n";
    if (part1_test_result().has_value()) {
        std::stringstream input(test_input().value());
        try {
            auto result = part1(input);
            if (result == part1_test_result().value()) {
                output << "Part 1 passed\n";
            } else {
                output << "Part 1 failed: Expected " << part1_test_result().value() << ", got " << result << "\n";
            }
        } catch (const std::exception& e) {
            output << "Part 1 failed: " << e.what() << "\n";
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
            }
        } catch (const std::exception& e) {
            output << "Part 2 failed: " << e.what() << "\n";
        }
    } else {
        output << "No test result for part 2\n";
    }

    return output.str();
}

std::string Day::run()
{
    std::ostringstream output;

    output << "Day " << day() << ": ";
    std::string filename = "data/day" + std::to_string(day()) + ".dat";
    std::ifstream input(filename, std::ios::in);

    if (!input.is_open()) {
        output << "Could not open file " << filename << "\n";
        return output.str();
    }

    try {
        auto result = part1(input);
        output << result;
    } catch (const std::exception& e) {
        output << "Error: " << e.what();
    }

    output << "   ";

    input.clear();
    input.seekg(0, std::ios::beg);

    try {
        auto result = part2(input);
        output << result;
    } catch (const std::exception& e) {
        output << "Error: " << e.what();
    }
    output << "\n";

    return output.str();
}

int main(int argc, char** argv)
{
    std::vector<Day*> days = { new Day1, new Day2 };

    if (argc > 1 && std::string(argv[1]) == "t") {
        for (auto& day : days) {
            std::cout << day->test();
        }
    } else {
        for (auto& day : days) {
            std::cout << day->run();
        }
    }

    return 0;
}
