#pragma once
#include <chrono>
#include "SingleBlink.h"
using namespace std::chrono_literals;

class SnakeGame;

class Booster : public SingleBlink
{
    inline static constexpr auto BOOSTER_SPEEDS = { 25ms, 75ms, 100ms, 125ms, 150ms };
    static std::chrono::milliseconds getRandomSpeed();

public:
    const std::chrono::milliseconds boosting;

    Booster(SnakeGame& parent);
};
