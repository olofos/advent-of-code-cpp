#pragma once
#ifndef AOC_UTIL_H
#define AOC_UTIL_H

namespace aoc {
class Point {
public:
    int x;
    int y;

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

Point operator-(const Point& lhs, const Point& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
Point operator*(int lhs, const Point& rhs) { return { lhs * rhs.x, lhs * rhs.y }; }
}

#endif
