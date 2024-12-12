#include <istream>
#include <string>
#include <vector>

#include "util.h"

namespace aoc {

std::vector<std::string> read_lines(std::istream& input)
{
    std::string line;
    std::vector<std::string> lines;
    while (getline(input, line)) {
        lines.emplace_back(line);
    }
    return lines;
}

std::vector<std::string> extend(const std::vector<std::string>& lines, char border)
{
    std::vector<std::string> extended;
    extended.reserve(lines.size() + 2);
    extended.push_back(std::string(lines[0].size() + 2, border));
    for (const auto& line : lines) {
        extended.emplace_back(border + line + border);
    }
    extended.push_back(std::string(lines[0].size() + 2, border));

    return extended;
}

std::vector<std::string> read_lines_with_border(std::istream& input, char border)
{
    return extend(read_lines(input), border);
}
}