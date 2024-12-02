#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "day.h"

std::pair<std::vector<int>, std::vector<int>> parse(std::istream& input)
{
    int a, b;
    std::vector<int> values1;
    std::vector<int> values2;

    while (input >> a >> b) {
        values1.push_back(a);
        values2.push_back(b);
    }
    std::sort(values1.begin(), values1.end());
    std::sort(values2.begin(), values2.end());

    return { values1, values2 };
}

std::string Day1::part1(std::istream& input)
{
    auto [values1, values2] = parse(input);

    int sum = 0;
    for (unsigned i = 0; i < values1.size(); i++) {
        int d = values1[i] - values2[i];
        if (d > 0) {
            sum += d;
        } else {
            sum -= d;
        }
    }

    return std::to_string(sum);
}

std::string Day1::part2(std::istream& input)
{
    auto [values1, values2] = parse(input);

    int sum = 0;
    for (auto value1 : values1) {
        int count = 0;
        for (auto value2 : values2) {
            if (value2 == value1) {
                count++;
            }
        }
        sum += count * value1;
    }

    return std::to_string(sum);
}