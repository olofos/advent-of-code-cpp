#include <algorithm>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "days.h"

namespace day19 {
struct Trie {
    std::map<char, Trie> children;
    bool is_leaf;

    Trie()
        : is_leaf(false)
    {
    }

    Trie(const std::vector<std::string>& patterns)
        : is_leaf(false)
    {
        for (const auto& pattern : patterns) {
            add(pattern);
        }
    }

    void add(const std::string_view& str)
    {
        if (str.empty()) {
            is_leaf = true;
            return;
        }
        children[str[0]].add(str.substr(1));
    }
};

std::pair<std::vector<std::string>, std::vector<std::string>> parse(std::istream& input)
{
    std::string line;
    std::getline(input, line);
    std::vector<std::string> patterns;

    std::stringstream ss(line);
    std::string pattern;
    while (ss >> pattern) {
        if (pattern.ends_with(",")) {
            pattern.pop_back();
        }
        patterns.push_back(pattern);
    }

    std::vector<std::string> strings;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }
        strings.push_back(line);
    }
    return { patterns, strings };
}

std::size_t count_matches(const Trie& trie, const std::string_view& str)
{
    std::vector<std::pair<const Trie*, std::size_t>> nodes = { { &trie, 1 } };

    for (auto c : str) {
        std::vector<std::pair<const Trie*, std::size_t>> new_nodes;
        for (auto [node, node_count] : nodes) {
            auto it = node->children.find(c);
            if (it != node->children.end()) {
                new_nodes.push_back({ &it->second, node_count });
            }
        }
        auto root_count = std::accumulate(new_nodes.begin(), new_nodes.end(), std::size_t {}, [](auto a, auto b) { return b.first->is_leaf ? a + b.second : a; });
        new_nodes.push_back({ &trie, root_count });
        nodes = new_nodes;
    }

    auto count = std::accumulate(nodes.begin(), nodes.end(), std::size_t {}, [](auto a, auto b) { return b.first->is_leaf ? a + b.second : a; });

    return count;
}

std::string part1(std::istream& input)
{
    auto [patterns, strings] = parse(input);
    Trie trie(patterns);
    auto count = std::count_if(strings.begin(), strings.end(), [&](auto& str) { return count_matches(trie, str) > 0; });
    return std::to_string(count);
}

std::string part2(std::istream& input)
{
    auto [patterns, strings] = parse(input);
    Trie trie(patterns);
    auto count = std::accumulate(strings.begin(), strings.end(), uint64_t {}, [&](auto a, auto& str) { return a + count_matches(trie, str); });
    return std::to_string(count);
}
}

DayDescription Day19::description()
{
    DayDescription description { 19, 2024 };
    description.part1 = day19::part1;
    description.part2 = day19::part2;
    description.part1_test_result = "6";
    description.part2_test_result = "16";
    description.test_input = "r, wr, b, g, bwu, rb, gb, br\n\nbrwrr\nbggr\ngbbr\nrrbgbr\nubwu\nbwurrg\nbrgr\nbbrgwb";
    return description;
}
