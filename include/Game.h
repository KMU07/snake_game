#pragma once
#include <chrono>
#include "Pixel.h"

class GameObject;
class GameEngine;

class Game
{
    GameEngine& engine;

public:
    bool enabled = true;

    Game();

    void setRenderDelay(std::chrono::milliseconds delay);
    void setDefaultColor(Color bgColor, Color chColor);

    virtual void update();

    void run();
};
