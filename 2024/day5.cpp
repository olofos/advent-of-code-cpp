#include <algorithm>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day5 {

struct Input {
    std::set<std::pair<int, int>> ordering;
    std::vector<std::vector<int>> pages_list;
};

Input parse(std::istream& input)
{
    std::string line;
    std::set<std::pair<int, int>> ordering;

    while (std::getline(input, line)) {
        if (line == "") {
            break;
        }

        auto pos = line.find("|");
        if (pos == std::string::npos) {
            throw std::runtime_error("invalid input '" + line + "'");
        }

        auto low = std::stoi(line.substr(0, pos));
        auto high = std::stoi(line.substr(pos + 1));

        ordering.insert(std::make_pair(low, high));
    }

    std::vector<std::vector<int>> pages_list;
    while (std::getline(input, line)) {
        std::stringstream ss(line);
        std::vector<int> pages;
        std::string entry;
        while (std::getline(ss, entry, ',')) {
            pages.push_back(std::stoi(entry));
        }
        pages_list.emplace_back(std::move(pages));
    }

    return { ordering, pages_list };
}

bool check_ordering(const std::set<std::pair<int, int>>& ordering, const std::vector<int>& pages)
{
    for (auto it1 = pages.begin(); it1 != pages.end(); ++it1) {
        for (auto it2 = it1 + 1; it2 != pages.end(); ++it2) {
            if (ordering.find({ *it2, *it1 }) != ordering.end()) {
                return false;
            }
        }
    }
    return true;
}

void sort(const std::set<std::pair<int, int>>& ordering, std::vector<int>& pages)
{
    bool did_swap;
    do {
        did_swap = false;
        for (auto it = pages.begin(); it != pages.end() - 1; ++it) {

            auto a = it[0];
            auto b = it[1];
            if (ordering.find({ b, a }) != ordering.end()) {

                std::iter_swap(it, it + 1);
                did_swap = true;
            }
        }
    } while (did_swap);
}

std::string part1(std::istream& input)
{
    auto [ordering, pages_list] = parse(input);
    int sum = 0;
    for (auto& pages : pages_list) {
        if (check_ordering(ordering, pages)) {
            sum += pages[pages.size() / 2];
        }
    }

    return std::to_string(sum);
}

std::string part2(std::istream& input)
{
    auto [ordering, pages_list] = parse(input);
    int sum = 0;
    for (auto& pages : pages_list) {
        if (!check_ordering(ordering, pages)) {
            sort(ordering, pages);
            sum += pages[pages.size() / 2];
        }
    }

    return std::to_string(sum);
}
}

DayDescription Day5::description()
{
    DayDescription description { 5, 2024 };
    description.part1 = day5::part1;
    description.part2 = day5::part2;
    description.part1_test_result = "143";
    description.part2_test_result = "123";
    description.test_input = "47|53\n97|13\n97|61\n97|47\n75|29\n61|13\n75|53\n29|13\n97|29\n53|29\n61|53\n97|53\n61|29\n47|13\n75|47\n97|75\n47|61\n75|61\n47|29\n75|13\n53|13\n\n75,47,61,53,29\n97,61,53,29,13\n75,29,13\n75,97,47,61,53\n61,13,29\n97,13,75,29,47\n";
    return description;
}
