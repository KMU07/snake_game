#pragma once
#include "TextBox.h"
#include "SnakeStatus.h"

class Mission :public TextBox
{
    SnakeStatus& status;

public:
    uint16_t wallBounceGoal = 0;
    uint16_t boosterGoal = 0;
    uint16_t appleGoal = 0;
    uint16_t poisonGoal = 0;
    uint16_t gatePassGoal = 0;

public:
    Mission(SnakeStatus& staus);

    bool allSuccess() const;

    void updateText() final;
};
