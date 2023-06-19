#include <string>
#include "GameOverBoard.h"

GameOverBoard::GameOverBoard(const std::string reasonOfDeath)
    : TextBox("GameOverBoard"), deathMessage(reasonOfDeath)
{
    boxX = boxY = 0;
    width = 80;
    height = 10;

    resize_term(height + 1, width + 1);
}

void GameOverBoard::updateText()
{
    const std::string& title = "|| Game over ||";
    for (size_t i = 0; i < title.length(); i++)
    {
        Pixel p;

        p.pos = Vector2Int(boxX + i + 1, boxY + 1);
        p.ch = title[i];
        texts.push_back(p);
    }

    for (size_t i = 0; i < deathMessage.length(); i++)
    {
        Pixel p;

        p.pos = Vector2Int(boxX + i + 1, boxY + height / 2);
        p.ch = deathMessage[i];
        texts.push_back(p);
    }
}
