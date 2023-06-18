#pragma once
#include "TextBox.h"
#include "SnakeStatus.h"

class Mission :public TextBox
{
    SnakeStatus& status;
public:
    uint16_t wallBounceGoal;
    uint16_t boosterGoal;
    uint16_t appleGoal;
    uint16_t poisonGoal;
    uint16_t gatePassGoal;

public:
    Mission(SnakeStatus& staus);
    void updateText() final;
};
