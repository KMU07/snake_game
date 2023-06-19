#include "Wall.h"

Wall::Wall(Vector2Int pos, bool immune, bool bounce)
    : immune(immune), bounce(bounce), GameObject("Wall", 1)
{
    Pixel pixel;

    if (bounce)
        pixel.ch = '@';

    pixel.chColor = Color::White;
    pixel.pos = pos;

    pixels.push_back(pixel);
}

bool Wall::isGate() const
{
    return false;
}
