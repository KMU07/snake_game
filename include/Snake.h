#pragma once
#include "GameObject.h"

class Snake : public GameObject
{
public:
    enum Direction
    {
        Up = 0,
        Down,
        Left,
        Right
    };

    Snake(std::string tag, Direction direction, uint16_t x, uint16_t y);
    virtual void update();
    uint16_t getBodyLength() const;
    void addTail();
    void removeTail();
    bool isDead() const;

private:
    const int8_t dx[4] = {0, 0, -1, 1};
    const int8_t dy[4] = {1, -1, 0, 0};

    Direction headDirection;
};
