#pragma once
#ifndef AOC_UTIL_H
#define AOC_UTIL_H

namespace aoc {
class Point {
public:
    int x;
    int y;

    Point()
        : x(0)
        , y(0)
    {
    }

    Point(int x, int y)
        : x(x)
        , y(y)
    {
    }

    Point(unsigned x, unsigned y)
        : x(x)
        , y(y)
    {
    }
    auto operator<=>(const Point&) const = default;

    Point operator+=(const Point& other) { return { x += other.x, y += other.y }; }
};

inline Point operator+(const Point& lhs, const Point& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }
inline Point operator-(const Point& lhs, const Point& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
inline Point operator*(int lhs, const Point& rhs) { return { lhs * rhs.x, lhs * rhs.y }; }

std::vector<std::string> read_lines(std::istream& input);
std::vector<std::string> read_lines_with_border(std::istream& input, char border = '.');
}

#endif
