#include <algorithm>
#include <array>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day25 {
std::string part1(std::istream& input)
{
    std::vector<std::array<unsigned, 5>> keys;
    std::vector<std::array<unsigned, 5>> locks;

    for (;;) {
        std::string line;
        bool is_lock = false;
        if (!std::getline(input, line)) {
            break;
        }
        if (line == "#####") {
            is_lock = true;
        }
        std::array<unsigned, 5> count = { 0, 0, 0, 0, 0 };
        for (int i = 0; i < 5; i++) {
            std::getline(input, line);
            for (int j = 0; j < 5; j++) {
                if (line[j] == '#') {
                    count[j]++;
                }
            }
        }
        if (is_lock) {
            locks.push_back(count);
        } else {
            keys.push_back(count);
        }
        std::getline(input, line);
        std::getline(input, line);
    }

    unsigned count = 0;
    for (auto& key : keys) {
        for (auto& lock : locks) {
            bool fits = true;
            for (int i = 0; i < 5; i++) {
                if (key[i] + lock[i] >= 6) {
                    fits = false;
                    break;
                }
            }
            if (fits) {
                count++;
            }
        }
    }

    return std::to_string(count);
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day25::description()
{
    DayDescription description { 25, 2024 };
    description.part1 = day25::part1;
    description.part2 = day25::part2;
    description.part1_test_result = "3";
    // description.part2_test_result = "";
    description.test_input = "#####\n.####\n.####\n.####\n.#.#.\n.#...\n.....\n\n#####\n##.##\n.#.##\n...##\n...#.\n...#.\n.....\n\n.....\n#....\n#....\n#...#\n#.#.#\n#.###\n#####\n\n.....\n.....\n#.#..\n###..\n###.#\n###.#\n#####\n\n.....\n.....\n.....\n#....\n#.#..\n#.#.#\n#####";
    return description;
}
