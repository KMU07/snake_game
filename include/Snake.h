#pragma once
#include <string>
#include <chrono>
#include "GameObject.h"
#include "SnakeStatus.h"
#include "Vector2Int.h"
using namespace std::chrono_literals;

class Snake : public GameObject
{
public:
    SnakeStatus& status;

private:
    static constexpr auto SNAKE_MOVE_INTERVAL = 500ms;
    static constexpr auto INPUT_INTERVAL = 1ms;

    static const Color headColor;
    static const Color bodyColor;

    std::chrono::milliseconds boosted = 0ms;
    Vector2Int headDirection;
    Vector2Int tailDirection;

    uint16_t lenBodyNotGateThrough = 0;
    bool passingGate = false;

    std::string reasonOfDeath = "";
    bool dead = false;

    void addHead();
    void popHead();
    void addTail();
    void popTail();

public:
    Snake(SnakeStatus& status, Vector2Int head, Vector2Int body, Vector2Int tail);

    bool isPassingGate() const;
    bool isDead() const;

    size_t getBodyLength() const;

    std::string getReasonOfDeath() const;

    void update() final;

    void onCollision(GameObject* other);
};
