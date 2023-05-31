#include <chrono>
#include <queue>
#include <map>
#include "Renderer.h"
#include "Game.h"

void InvokeManager::addInvoke(Time nextInvokeTime, Callback callback, const MilliSec interval, const bool isRepeat)
{
    size_t targetIndex = invokes.size();

    for (size_t i = 0; i < invokes.size(); i++)
    {
        if (std::get<Time>(invokes[i]) > nextInvokeTime)
        {
            targetIndex = i;
            break;
        }
    }

    invokes.insert(invokes.begin() + targetIndex, { nextInvokeTime, interval, callback, isRepeat });
}

void InvokeManager::invokeOnce(Callback callback, const MilliSec delay)
{
    const Time nextInvokeTime = std::chrono::system_clock::now() + delay;
    addInvoke(nextInvokeTime, callback, delay, false);
}

void InvokeManager::invokeRepeat(Callback callback, const MilliSec ms)
{
    const Time nextInvokeTime = std::chrono::system_clock::now() + ms;
    addInvoke(nextInvokeTime, callback, ms, true);
}

void InvokeManager::checkAndInvoke()
{
    std::queue<std::tuple<Time, MilliSec, Callback, bool>> invokeQueue;

    // Time cheking needs to be done quickly, and pop_back later.
    const Time now = std::chrono::system_clock::now();
    for (size_t i = 0; i < invokes.size(); i++)
    {
        if (std::get<Time>(invokes[i]) < now)
            break;

        invokeQueue.push(invokes[i]);
    }

    // Remove invoked callbacks.
    const size_t invokedSize = invokeQueue.size();
    invokes.erase(invokes.begin(), invokes.begin() + invokedSize);

    // Call callback function and push_back again to invokes if isRepeat is true.
    while (!invokeQueue.empty())
    {
        auto& [prevInvokeTime, interval, callback, isRepeat] = invokeQueue.front();
        invokeQueue.pop();

        callback();

        if (isRepeat)
        {
            const Time nextInvokeTime = prevInvokeTime + interval;
            this->addInvoke(nextInvokeTime, callback, interval, isRepeat);
        }
    }
}

void Game::run()
{
    this->start();

    // Game loop
    while (!gameEnd)
    {
        const Time startTime = std::chrono::system_clock::now();

        invokeManager.checkAndInvoke();
        this->processObjectsCollision();

        if (gameEnd)
            break;

        // Update state and collision check
        this->update();
        this->processObjectsCollision();

        if (gameEnd)
            break;

        renderer.renderWorld();

        std::this_thread::sleep_until(startTime + frameDelay);
    }
}

void Game::setFrameDelay(const MilliSec delay)
{
    frameDelay = delay;
}

void Game::invoke(Callback callback, const MilliSec delay)
{
    invokeManager.invokeOnce(callback, delay);
}

void Game::invokeRepeat(Callback callback, const MilliSec interval)
{
    invokeManager.invokeRepeat(callback, interval);
}

void Game::addCollisionable(GameObject* const obj, OnCollision callback, const uint16_t colliderOrder)
{
    size_t targetIndex = collisionables.size();

    // Find the index where this object should be inserted.
    for (size_t i = 0; i < collisionables.size(); i++)
    {
        const uint16_t nowColliderOrder = std::get<uint16_t>(collisionables[i]);

        if (nowColliderOrder > colliderOrder)
        {
            targetIndex = i;
            break;
        }
    }

    collisionables.insert(
        collisionables.begin() + targetIndex,
        std::make_tuple(colliderOrder, obj, callback)
    );
}

void Game::popCollisionable(GameObject* const obj)
{
    for (auto itr = collisionables.begin(); itr != collisionables.end(); ++itr)
    {
        GameObject* nowObj = std::get<GameObject*>(*itr);

        if (nowObj == obj)
        {
            collisionables.erase(itr);
            break;
        }
    }
}

void Game::processObjectsCollision()
{
    // TODO: Implement
    // ...
    throw std::exception("Not Implemented");
}
