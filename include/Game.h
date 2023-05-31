#pragma once
#include <functional>
#include <chrono>
#include <deque>
#include <map>

class GameObject;
class Renderer;

using Time = std::chrono::system_clock::time_point;
using MilliSec = std::chrono::milliseconds;

using OnCollision = std::function<void(GameObject* const)>;
using Callback = std::function<void()>;

class InvokeManager final
{
    std::deque<std::tuple<Time, MilliSec, Callback, bool>> invokes;

    // Add invoke function.
    void addInvoke(Time invokedTime, Callback callback, MilliSec interval, bool isRepeat);

public:
    void invokeOnce(Callback callback, MilliSec delay);
    void invokeRepeat(Callback callback, MilliSec interval);

    // Check invokes and execute timeouted callbacks.
    void checkAndInvoke();
};

class Game
{
    Renderer& renderer;
    MilliSec frameDelay;

    std::deque<std::tuple<uint16_t, GameObject*, OnCollision>> collisionables;
    InvokeManager invokeManager;

    bool gameEnd = false;

public:
    // Start the game loop.
    virtual void run() final;

private:
    // Initialize game state before running the game loop.
    virtual void start() = 0;

    // Called every game loop to update game state.
    virtual void update() = 0;

protected:
    virtual void setFrameDelay(MilliSec delay) final;

    virtual void invoke(Callback callback, MilliSec delay) final;
    virtual void invokeRepeat(Callback callback, MilliSec interval) final;

    virtual void addCollisionable(GameObject* obj, OnCollision callback, uint16_t colliderOrder = 0) final;
    virtual void popCollisionable(GameObject* obj) final;

    virtual void processObjectsCollision() final;
};
