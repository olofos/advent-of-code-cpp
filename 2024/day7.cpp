#include <algorithm>
#include <iostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace {
std::vector<std::pair<uint64_t, std::vector<uint64_t>>> parse(std::istream& input)
{
    std::vector<std::pair<uint64_t, std::vector<uint64_t>>> result;

    std::string line;
    while (std::getline(input, line)) {
        std::stringstream ss(line);

        uint64_t sum;
        ss >> sum;

        char c;
        ss >> c;

        if (c != ':') {
            throw std::runtime_error("invalid input");
        }

        std::vector<uint64_t> terms;
        uint64_t term;
        while (ss >> term) {
            terms.push_back(term);
        }

        result.push_back(std::make_pair(sum, terms));
    }

    return result;
}

}

std::string Day7::part1(std::istream& input)
{
    auto list = parse(input);
    uint64_t total = 0;
    for (auto& [sum, terms] : list) {
        for (uint32_t bits = 0; bits < (1u << (terms.size() - 1)); bits++) {
            uint64_t s = terms[0];
            for (uint64_t i = 0; i < terms.size() - 1; i++) {
                if (bits & (1 << i)) {
                    s += terms[i + 1];
                } else {
                    s *= terms[i + 1];
                }
            }
            if (s == sum) {
                total += sum;
                break;
            }
        }
    }

    return std::to_string(total);
}

std::string Day7::part2(std::istream&)
{
    throw std::runtime_error("Not implemented");
}