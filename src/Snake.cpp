#include "Snake.h"

Snake::Snake(std::string tag, Direction direction, uint16_t x, uint16_t y)
    : GameObject(tag), headDirection(direction)
{
    for (int i = 0; i < 2; i++)
        this->pixels.push_back({'@', x, y});
}

void Snake::update()
{
    // 앞쪽 몸체의 위치로 이동
    for (int i = pixels.size() - 1; i > 0; i--)
        this->pixels[i] = this->pixels[i - 1];

    // 머리 위치 이동
    this->pixels[0].x += this->dx[headDirection];
    this->pixels[0].y += this->dy[headDirection];
}

bool Snake::isDead() const
{
    return this->pixels.size() < 3;
}

void Snake::addTail()
{
    this->pixels.push_back(this->pixels.back());
}

void Snake::removeTail()
{
    this->pixels.pop_back();
}

uint16_t Snake::getBodyLength() const
{
    return this->pixels.size();
}
