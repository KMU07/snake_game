#include <chrono>
#include <random>
#include "SnakeGame.h"
#include "Booster.h"

std::chrono::milliseconds Booster::getRandomSpeed()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    static std::uniform_int_distribution<int> dis(0, std::size(BOOSTER_SPEEDS));

    return *(BOOSTER_SPEEDS.begin() + dis(gen));
}

Booster::Booster(SnakeGame& parent)
    : boosting(getRandomSpeed()), SingleBlink("Booster", parent, Color::Cyan, 10s)
{}
