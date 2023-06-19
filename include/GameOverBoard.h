#pragma once
// #include "TextBox.h"
#include <string>
#include "GameObject.h"

// 임시!
class GameOverBoard : public GameObject
{
public:
    GameOverBoard(std::string txt)
        : GameObject("TEMP", 0)
    {
        int x = 0;
        for (char c : txt)
        {
            Pixel p;

            p.pos = Vector2Int(x++, 0);
            p.ch = c;
            pixels.push_back(p);
        }
    }

    bool isCollisionable() const final
    {
        return false;
    }

};
