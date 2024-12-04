#include <cstdlib>
#include <istream>
#include <string>
#include <utility>
#include <vector>

#include "days.h"

namespace {
std::vector<std::string> read_lines(std::istream& input)
{
    std::string line;
    std::vector<std::string> lines;
    while (getline(input, line)) {
        lines.emplace_back(line);
    }
    return lines;
}

std::vector<std::pair<int, int>> get_offsets(std::size_t x, std::size_t y, std::size_t width, std::size_t height)
{
    std::vector<std::pair<int, int>> offsets;
    if (x < width - 3) {
        offsets.push_back({ 1, 0 });
        if (y < height - 3) {
            offsets.push_back({ 1, 1 });
        }
        if (y > 2) {
            offsets.push_back({ 1, -1 });
        }
    }
    if (y < height - 3) {
        offsets.push_back({ 0, 1 });
    }
    if (y > 2) {
        offsets.push_back({ 0, -1 });
    }
    if (x > 2) {
        offsets.push_back({ -1, 0 });
        if (y < height - 3) {
            offsets.push_back({ -1, 1 });
        }
        if (y > 2) {
            offsets.push_back({ -1, -1 });
        }
    }
    return offsets;
}
}

std::string Day4::part1(std::istream& input)
{
    auto lines = read_lines(input);

    int count = 0;
    for (std::size_t y = 0; y < lines.size(); y++) {
        for (std::size_t x = 0; x < lines[y].size(); x++) {
            if (lines[y][x] == 'X') {
                auto offsets = get_offsets(x, y, lines[y].size(), lines.size());

                for (auto& [dx, dy] : offsets) {
                    bool has_m = lines[y + dy][x + dx] == 'M';
                    bool has_a = lines[y + 2 * dy][x + 2 * dx] == 'A';
                    bool has_s = lines[y + 3 * dy][x + 3 * dx] == 'S';

                    count += has_m && has_a && has_s;
                }
            }
        }
    }

    return std::to_string(count);
}

std::string Day4::part2(std::istream& input)
{
    auto lines = read_lines(input);

    int count = 0;
    for (size_t y = 1; y < lines.size() - 1; y++) {
        for (size_t x = 1; x < lines[y].size() - 1; x++) {
            if (lines[y][x] == 'A') {
                std::vector<std::pair<int, int>> offsets { { -1, -1 }, { 1, -1 }, { -1, 1 }, { 1, 1 } };

                bool nw_se = (lines[y - 1][x - 1] == 'M') && (lines[y + 1][x + 1] == 'S');
                bool se_nw = (lines[y + 1][x + 1] == 'M') && (lines[y - 1][x - 1] == 'S');
                bool ne_sw = (lines[y - 1][x + 1] == 'M') && (lines[y + 1][x - 1] == 'S');
                bool sw_ne = (lines[y + 1][x - 1] == 'M') && (lines[y - 1][x + 1] == 'S');

                count += (nw_se || se_nw) && (ne_sw || sw_ne);
            }
        }
    }

    return std::to_string(count);
}