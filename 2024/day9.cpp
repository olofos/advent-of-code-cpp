#include <algorithm>
#include <cstdint>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <optional>
#include <ranges>
#include <set>
#include <string>
#include <vector>

#include "days.h"

namespace {
namespace part1 {
    std::vector<std::optional<int>> parse(std::istream& input)
    {
        char c;
        bool is_free = false;
        int id = 0;
        std::vector<std::optional<int>> blocks;
        while (input >> c) {
            if (c < '0' || c > '9') {
                if (c == '\n') {
                    break;
                }
                throw std::runtime_error("invalid input");
            }
            std::optional<int> value;
            if (is_free) {
                value = std::nullopt;
                is_free = false;
            } else {
                value = id++;
                is_free = true;
            }
            for (int i = 0; i < c - '0'; i++) {
                blocks.push_back(value);
            }
        }
        return blocks;
    }

    void defrag(std::vector<std::optional<int>>& blocks)
    {
        unsigned head = 0;
        unsigned tail = blocks.size() - 1;

        while (head < tail) {
            if (blocks[head].has_value()) {
                head++;
            } else if (!blocks[tail].has_value()) {
                tail--;
            } else {
                std::swap(blocks[head], blocks[tail]);
                head++;
                tail--;
            }
        }
    }
}

uint64_t calc_check_sum(const std::vector<std::optional<int>>& blocks)
{
    uint64_t sum = 0;
    for (uint64_t i = 0; blocks[i].has_value(); i++) {
        sum += i * blocks[i].value();
    }
    return sum;
}
}

std::string Day9::part1(std::istream& input)
{
    auto blocks = part1::parse(input);
    part1::defrag(blocks);
    auto check_sum = calc_check_sum(blocks);
    return std::to_string(check_sum);
}

std::string Day9::part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
