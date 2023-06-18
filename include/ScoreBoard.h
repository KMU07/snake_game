#pragma once
#include "TextBox.h"
#include "SnakeStatus.h"

class ScoreBoard :public TextBox
{
    SnakeStatus& status;

public:
    ScoreBoard(SnakeStatus& staus);
    void updateText() final;
};
