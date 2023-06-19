#include <cassert>
#include <vector>
#include <set>
#include "Gate.h"

Gate::~Gate()
{
    original->enabled = true;
}

Gate::Gate(Wall* wall, const std::set<Vector2Int, UniqueVectorCompareator>& openedDir)
    : original(wall), Wall(wall->pixels[0].pos)
{
    pixels[0].chColor = Color::Magenta;

    original->enabled = false;
    enabled = true;

    const std::vector<Vector2Int> verticalAndHorizontal = {
        Vector2Int::up,
        Vector2Int::down,
        Vector2Int::left,
        Vector2Int::right
    };

    for (uint8_t enter = 0; enter < 4; enter++)
    {
        const Vector2Int enterDir = verticalAndHorizontal[enter];
        const std::vector<Vector2Int> exits = {
            enterDir,
            enterDir.rotateRight90(),
            enterDir.rotateLeft90(),
            enterDir.rotate180()
        };

        for (uint8_t exit = 0; exit < 4; exit++)
        {
            if (openedDir.find(exits[exit]) != openedDir.end())
            {
                enterExit[enterDir] = exits[exit];
                break;
            }
        }
    }
}

bool Gate::isGate() const
{
    return true;
}

std::pair<Vector2Int, Vector2Int> Gate::getExit(Vector2Int enterDirection) const
{
    assert(exit != nullptr);

    const Vector2Int exitDirection = exit->enterExit[enterDirection];
    const Vector2Int exitPosition = exit->pixels[0].pos + exitDirection;

    return { exitPosition, exitDirection };
}
