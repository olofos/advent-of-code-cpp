#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace {

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
}

std::string Day5::part1(std::istream& input)
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

std::string Day5::part2(std::istream&)
{
    throw std::runtime_error("not implemented");
}