#pragma once
#include <cstdint>

struct SnakeStatus
{
    uint16_t currentLength = 0;
    uint16_t maxLength = 0;
    uint16_t wallBounced = 0;
    uint16_t boosterGets = 0;
    uint16_t appleGets = 0;
    uint16_t poisonGets = 0;
    uint16_t gatePass = 0;

    SnakeStatus() = default;
};
