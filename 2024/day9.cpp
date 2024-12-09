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
        std::size_t head = 0;
        std::size_t tail = blocks.size() - 1;

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

namespace part2 {
    struct Block {
        std::optional<int> id;
        uint64_t size;
    };

    std::vector<Block> parse(std::istream& input)
    {
        char c;
        bool is_free = false;
        int id = 0;
        std::vector<Block> blocks;
        while (input >> c) {
            if (c < '0' || c > '9') {
                if (c == '\n') {
                    break;
                }
                throw std::runtime_error("invalid input");
            }
            uint64_t size = c - '0';
            if (is_free) {
                blocks.push_back({ std::nullopt, size });
                for (int i = 0; i < static_cast<int>(size) - 1; i++) {
                    blocks.emplace_back();
                }
                is_free = false;
            } else {
                blocks.emplace_back(id++, size);
                is_free = true;
            }
        }
        return blocks;
    }

    void defrag(std::vector<Block>& blocks)
    {
        for (std::size_t tail = blocks.size() - 1; tail > 0; tail--) {
            if (blocks[tail].id.has_value()) {
                for (std::size_t head = 0; head < tail; head++) {
                    if (!blocks[head].id.has_value() && blocks[head].size >= blocks[tail].size) {
                        std::swap(blocks[head].id, blocks[tail].id);
                        blocks[head + 1].size += blocks[head].size - blocks[tail].size;
                        blocks[head].size = blocks[tail].size;

                        break;
                    }
                }
            }
        }
    }

    std::vector<std::optional<int>> expand(const std::vector<Block>& blocks)
    {
        std::vector<std::optional<int>> result;
        for (auto block : blocks) {
            for (uint64_t i = 0; i < block.size; i++) {
                result.push_back(block.id);
            }
        }
        return result;
    }

}

uint64_t calc_checksum(const std::vector<std::optional<int>>& blocks)
{
    uint64_t sum = 0;
    for (uint64_t i = 0; i < blocks.size(); i++) {
        sum += i * blocks[i].value_or(0);
    }
    return sum;
}
}

std::string Day9::part1(std::istream& input)
{
    using namespace part1;
    auto blocks = parse(input);
    defrag(blocks);
    auto checksum = calc_checksum(blocks);
    return std::to_string(checksum);
}

std::string Day9::part2(std::istream& input)
{
    using namespace part2;
    auto blocks = parse(input);
    defrag(blocks);
    auto checksum = calc_checksum(expand(blocks));
    return std::to_string(checksum);
}
