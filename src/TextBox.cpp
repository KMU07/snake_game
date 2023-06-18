#include <string>
#include "GameObject.h"
#include "TextBox.h"
#include "Vector2Int.h"

TextBox::TextBox(const std::string tag)
    : GameObject(tag, 0)
{}

bool TextBox::isCollisionable() const
{
    return false;
}

void TextBox::update()
{
    //기존에 있는 것들을 지워버리는 것
    pixels.clear();//화면에 그려지는 글자 하나씩 
    texts.clear();
    //updateText -> Mission,ScoreBoard(subclass)에서 virtual 함수 구현
    this->updateText();
    for (Pixel p : texts)//in python for i in list
        pixels.push_back(p);

    //score board,mission board에 해당하는 테두리를 여기서 담당하는것
    //수직 테두리
    for (uint16_t y = 1; y < height - 1; y++)
    {
        Pixel p;
        p.ch = '│';
        p.pos = Vector2Int(boxX, boxY + y);

        pixels.push_back(p);

        p.pos = Vector2Int(boxX + width, boxY + y);
        pixels.push_back(p);
    }
    //수평 테두리
    for (uint16_t x = 1; x < width - 1; x++)
    {
        Pixel p;
        p.ch = '─';
        p.pos = Vector2Int(boxX + x, boxY);

        pixels.push_back(p);

        p.pos = Vector2Int(boxX + x, boxY + height);
        pixels.push_back(p);
    }

    Pixel p;
    //모서리 테두리
    p.ch = '┌';
    p.pos = Vector2Int(boxX, boxY);
    pixels.push_back(p);

    p.ch = '└';
    p.pos = Vector2Int(boxX, boxY + height);
    pixels.push_back(p);

    p.ch = '┐';
    p.pos = Vector2Int(boxX + width, boxY);
    pixels.push_back(p);

    p.ch = '┘';
    p.pos = Vector2Int(boxX + width, boxY + height);
    pixels.push_back(p);
}
