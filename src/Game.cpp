#include <chrono>
#include "Pixel.h"
#include "GameEngine.h"
#include "Game.h"

Game::Game()
    : engine(GameEngine::getInstance())
{}

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
        this->update();
        engine.processCollision();

        engine.updateAll();
        engine.processCollision();

        engine.render();
    }
}
