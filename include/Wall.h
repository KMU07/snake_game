#pragma once
#include "GameObject.h"

class Wall : public GameObject
{
public:
    const bool immune;
    const bool bounce;

    Wall(Vector2Int pos, bool immune = false, bool bounce = false);

    virtual bool isGate() const;
};
