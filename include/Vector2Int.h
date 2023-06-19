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

    Vector2Int(int32_t x = -1, int32_t y = -1);

    // Calculate the manhattan distance of a vector.
    // return: abs(vector.x) + abs(vector.y)
    int32_t manhattan() const;

    Vector2Int operator-() const;

    Vector2Int operator+(const Vector2Int& ref) const;
    Vector2Int operator-(const Vector2Int& ref) const;

    bool operator==(const Vector2Int& ref) const;
    bool operator!=(const Vector2Int& ref) const;

    Vector2Int& operator+=(const Vector2Int& ref);
    Vector2Int& operator-=(const Vector2Int& ref);

    Vector2Int rotateLeft90() const;
    Vector2Int rotateRight90() const;
    Vector2Int rotate180() const;
};

// x를 먼저 비교하고 같으면 y 비교
struct UniqueVectorCompareator
{
    bool operator()(const Vector2Int& a, const Vector2Int& b) const
    {
        return a.x == b.x ? (a.y < b.y) : (a.x < b.x);
    }
};
