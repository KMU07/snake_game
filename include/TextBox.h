#pragma once
#include "GameObject.h"
#include "Pixel.h"
#include <vector>
#include <string>
class TextBox :public GameObject
{
public:
    std::vector<Pixel> texts;
    uint16_t boxX, boxY;
    uint16_t width, height;
    bool isCollisionable() const final;
    TextBox(std::string tag);
private:
    virtual void updateText() = 0;
    void update() final;
};
