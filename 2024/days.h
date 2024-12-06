#pragma once
#ifndef AOC2024_DAYS_H
#define AOC2024_DAYS_H

#include <iostream>
#include <optional>
#include <string>

#include "day.h"

class Day1 : public Day {
public:
    std::string part1(std::istream& input) override;
    std::string part2(std::istream& input) override;
    int day() override { return 1; }
    int year() override { return 2024; }

    std::optional<std::string> part1_test_result() override { return "11"; };
    std::optional<std::string> part2_test_result() override { return "31"; };
    std::optional<std::string> test_input() override
    {
        return "3   4\n4   3\n2   5\n1   3\n3   9\n3   3";
    }
};

class Day2 : public Day {
public:
    std::string part1(std::istream& input) override;
    std::string part2(std::istream& input) override;
    int day() override { return 2; }
    int year() override { return 2024; }

    std::optional<std::string> part1_test_result() override { return "2"; };
    std::optional<std::string> part2_test_result() override { return "4"; };
    std::optional<std::string> test_input() override
    {
        return "7 6 4 2 1\n1 2 7 8 9\n9 7 6 2 1\n1 3 2 4 5\n8 6 4 4 1\n1 3 6 7 9";
    }
};

class Day3 : public Day {
public:
    std::string part1(std::istream& input) override;
    std::string part2(std::istream& input) override;
    int day() override { return 3; }
    int year() override { return 2024; }

    std::optional<std::string> part1_test_result() override { return "161"; };
    std::optional<std::string> part2_test_result() override { return "48"; };
    std::optional<std::string> test_input() override
    {
        return "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
    }
};

class Day4 : public Day {
public:
    std::string part1(std::istream& input) override;
    std::string part2(std::istream& input) override;
    int day() override { return 4; }
    int year() override { return 2024; }

    std::optional<std::string> part1_test_result() override { return "18"; };
    std::optional<std::string> part2_test_result() override { return "9"; };
    std::optional<std::string> test_input() override
    {
        return "MMMSXXMASM\nMSAMXMSMSA\nAMXSXMAAMM\nMSAMASMSMX\nXMASAMXAMM\nXXAMMXXAMA\nSMSMSASXSS\nSAXAMASAAA\nMAMMMXMMMM\nMXMXAXMASX\n";
    }
};

class Day5 : public Day {
public:
    std::string part1(std::istream& input) override;
    std::string part2(std::istream& input) override;
    int day() override { return 5; }
    int year() override { return 2024; }

    std::optional<std::string> part1_test_result() override { return "143"; };
    std::optional<std::string> part2_test_result() override { return "123"; };

    std::optional<std::string> test_input() override
    {
        return "47|53\n97|13\n97|61\n97|47\n75|29\n61|13\n75|53\n29|13\n97|29\n53|29\n61|53\n97|53\n61|29\n47|13\n75|47\n97|75\n47|61\n75|61\n47|29\n75|13\n53|13\n\n75,47,61,53,29\n97,61,53,29,13\n75,29,13\n75,97,47,61,53\n61,13,29\n97,13,75,29,47\n";
    }
};

class Day6 : public Day {
public:
    std::string part1(std::istream& input) override;
    std::string part2(std::istream& input) override;
    int day() override { return 6; }
    int year() override { return 2024; }

    std::optional<std::string> part1_test_result() override { return "41"; };
    std::optional<std::string> part2_test_result() override { return "6"; };

    std::optional<std::string> test_input() override
    {
        return "....#.....\n.........#\n..........\n..#.......\n.......#..\n..........\n.#..^.....\n........#.\n#.........\n......#...\n";
    }
};
#endif
