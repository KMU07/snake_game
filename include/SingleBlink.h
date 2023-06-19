#pragma once
#include <string>
#include <chrono>
#include "GameObject.h"
using namespace std::chrono_literals;

class SnakeGame;

// 일정 간격마다 스네이크 게임에서 빈 공간에 나타나고,
// 부딫히면 다른 위치에 나타나는 오브젝트
class SingleBlink : public GameObject
{
    std::chrono::system_clock::time_point prevSpawn = std::chrono::system_clock::now();
    std::chrono::milliseconds blinkInterval;

    SnakeGame& parent;

public:
    SingleBlink(
        std::string tag,
        SnakeGame& parent,
        Color chColor,
        std::chrono::milliseconds blinkInterval
    );

    void update() final;

    void onCollision(GameObject* other) final;
};
