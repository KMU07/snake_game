#pragma once
#include <cstdint>

// A simple 2d vector class without dot product and cross product etc.
class Vector2Int
{
public:
    int32_t x = 0;
    int32_t y = 0;

    static const Vector2Int up;
    static const Vector2Int down;
    static const Vector2Int left;
    static const Vector2Int right;
    static const Vector2Int zero;

    Vector2Int(int32_t x, int32_t y);

    // Calculate the manhattan distance of a vector.
    // return: abs(vector.x) + abs(vector.y)
    int32_t manhattan() const;

    Vector2Int operator-() const;

    Vector2Int operator+(const Vector2Int& ref) const;
    Vector2Int operator-(const Vector2Int& ref) const;

    bool operator==(const Vector2Int& ref) const;
    bool operator!=(const Vector2Int& ref) const;
};
