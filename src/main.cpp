#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "day.h"

void Day::test()
{
    if (!test_input().has_value()) {
        std::cout << "No test input for day " << day() << std::endl;
        return;
    }

    std::cout << "Running tests for day " << day() << std::endl;
    if (part1_test_result().has_value()) {
        std::stringstream input(test_input().value());
        try {
            auto result = part1(input);
            if (result == part1_test_result().value()) {
                std::cout << "Part 1 passed" << std::endl;
            } else {
                std::cout << "Part 1 failed: Expected " << part1_test_result().value() << ", got " << result << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Part 1 failed: " << e.what() << std::endl;
        }
    } else {
        std::cout << "No test result for part 1" << std::endl;
    }

    if (part2_test_result().has_value()) {
        std::stringstream input(test_input().value());
        try {
            auto result = part2(input);
            if (result == part2_test_result().value()) {
                std::cout << "Part 2 passed" << std::endl;
            } else {
                std::cout << "Part 2 failed: Expected " << part2_test_result().value() << ", got " << result << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Part 2 failed: " << e.what() << std::endl;
        }
    } else {
        std::cout << "No test result for part 2" << std::endl;
    }
}

void Day::run()
{
    auto n = day();
    std::cout << "Day " << n << ": ";
    std::string filename = "data/day" + std::to_string(n) + ".dat";
    std::ifstream input(filename, std::ios::in);

    if (!input.is_open()) {
        std::cout << "Could not open file " << filename << std::endl;
    }

    try {
        auto result = part1(input);
        std::cout << result;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what();
    }

    std::cout << "   ";

    input.clear();
    input.seekg(0, std::ios::beg);

    try {
        auto result = part2(input);
        std::cout << result;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what();
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<Day*> days = { new Day1, new Day2 };

    if (argc > 1 && std::string(argv[1]) == "t") {
        for (auto day : days) {
            day->test();
        }
    } else {
        for (auto day : days) {
            day->run();
        }
    }

    return 0;
}
