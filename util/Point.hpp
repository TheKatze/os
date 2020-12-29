#pragma once

template<typename T>
struct Point {
    Point<T>() = default;
    Point<T>(T x, T y)
    : x(x)
    , y(y) {}

    T x;
    T y;

    bool operator==(Point<T> rhs) {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(Point<T> rhs) {
        return !operator==(rhs);
    }
};
