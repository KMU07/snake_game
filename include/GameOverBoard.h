#pragma once
#include <string>
#include "TextBox.h"

class GameOverBoard : public TextBox
{
    const std::string deathMessage;

public:
    GameOverBoard(std::string reasonOfDeath);

    void updateText() final;
};
