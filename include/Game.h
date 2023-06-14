#pragma once
#include <chrono>

class GameObject;
class GameEngine;

class Game
{
    GameEngine& engine = GameEngine::getInstance();

public:
    bool enabled = true;

    void setRenderDelay(std::chrono::milliseconds delay);
    void setDefaultColor(Color bgColor, Color chColor);

    virtual void update();

    void run();
};
