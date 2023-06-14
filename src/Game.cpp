#include <chrono>
#include "GameEngine.h"
#include "Game.h"

void Game::setRenderDelay(const std::chrono::milliseconds delay)
{
    engine.renderDelay = delay;
}

void Game::setDefaultColor(const Color bgColor, const Color chColor)
{
    engine.defaultbgColor = bgColor;
    engine.defaultChColor = chColor;
}

void Game::update()
{}

void Game::run()
{
    while (enabled)
    {
        engine.updateAll();
        engine.processCollision();

        this->update();
        engine.processCollision();

        engine.render();
    }
}
