#pragma once

struct Point {
    int x;
    int y;
};

struct UPoint {
    UPoint() = default;
    UPoint(unsigned int x, unsigned int y)
    : x(x)
    , y(y) {}

    unsigned int x;
    unsigned int y;
};
