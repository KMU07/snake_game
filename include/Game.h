#pragma once
#include <functional>
#include <chrono>
#include <deque>
#include <map>

class GameObject;
class Renderer;

using Time = std::chrono::system_clock::time_point;
using Delay = std::chrono::duration<long long, std::ratio<1, 1000000>>;

using OnCollision = std::function<void(GameObject* const)>;
using Callback = std::function<void()>;

class InvokeManager final
{
    std::deque<std::tuple<Time, Delay, Callback, bool>> invokes;

    // Add invoke function.
    void addInvoke(Time invokedTime, Callback callback, Delay delay, bool isRepeat);

public:
    void invokeOnce(Callback callback, Delay delay);
    void invokeRepeat(Callback callback, Delay interval);

    // Check invokes and execute timeouted callbacks.
    void checkAndInvoke();
};

class Game
{
    Renderer& renderer;
    Delay frameDelay;

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
    virtual void setFrameDelay(Delay delay) final;

    virtual void invoke(Callback callback, Delay delay) final;
    virtual void invokeRepeat(Callback callback, Delay interval) final;

    virtual void addCollisionable(GameObject* obj, OnCollision callback, uint16_t colliderOrder = 0) final;
    virtual void popCollisionable(GameObject* obj) final;

    virtual void processObjectsCollision() final;
};
