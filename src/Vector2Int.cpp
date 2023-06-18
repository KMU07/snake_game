#include <stdlib.h>
#include "Vector2Int.h"

const Vector2Int Vector2Int::up(0, -1);
const Vector2Int Vector2Int::down(0, 1);
const Vector2Int Vector2Int::left(-1, 0);
const Vector2Int Vector2Int::right(1, 0);
const Vector2Int Vector2Int::zero(0, 0);

Vector2Int::Vector2Int(int32_t x, int32_t y)
{
    this->x = x;
    this->y = y;
}

int32_t Vector2Int::manhattan() const
{
    return abs(this->x) + abs(this->y);
}

Vector2Int Vector2Int::operator-() const
{
    return { -x, -y };
}

Vector2Int Vector2Int::operator+(const Vector2Int& ref) const
{
    return { x + ref.x, y + ref.y };
}

Vector2Int Vector2Int::operator-(const Vector2Int& ref) const
{
    return *this + -ref;
}

bool Vector2Int::operator==(const Vector2Int& ref) const
{
    return x == ref.x && y == ref.y;
}

bool Vector2Int::operator!=(const Vector2Int& ref) const
{
    return !operator==(ref);
}
