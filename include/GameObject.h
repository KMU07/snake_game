#pragma once
#include <deque>
#include <string>
#include "Pixel.h"

class GameEngine;

class GameObject
{
    GameEngine& engine;

public:
    const uint16_t processOrder;
    const std::string tag;

    std::deque<Pixel> pixels;
    bool enabled = true;

    virtual ~GameObject();

    explicit GameObject(const std::string& tag, uint16_t procOrder = 0);

    // Always return true as default.
    // If you inherit this class and create new class that is not collisionable,
    // you can modify this function's return value.
    virtual bool isCollisionable() const;

    // This function will be called for every game loop.
    virtual void update();

    virtual void onCollision(GameObject* const other) = 0;
};
