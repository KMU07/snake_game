#include <string>
#include <chrono>
#include <cassert>
#include "SingleBlink.h"
#include "SnakeGame.h"

SingleBlink::SingleBlink(
    const std::string tag,
    SnakeGame& parent,
    Color chColor,
    std::chrono::milliseconds blinkInterval
)
    : parent(parent), blinkInterval(blinkInterval), GameObject(tag, 1)
{
    Pixel pixel;

    pixel.chColor = chColor;
    pixel.pos = parent.useRandEmptyPos();

    pixels.push_back(pixel);
}

void SingleBlink::update()
{
    const auto now = std::chrono::system_clock::now() - blinkInterval;

    if (prevSpawn + blinkInterval > now)
        return;
    prevSpawn += blinkInterval;

    assert(pixels.size() == 1);

    pixels[0].pos = parent.useRandEmptyPos();
}

void SingleBlink::onCollision(GameObject* other)
{
    assert(pixels.size() == 1);
    pixels[0].pos = parent.useRandEmptyPos();

    prevSpawn = std::chrono::system_clock::now();
}
