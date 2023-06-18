#pragma once
#include <curses.h>
#include "Vector2Int.h"

enum Color
{
    Black = COLOR_BLACK,
    Red = COLOR_RED,
    Green = COLOR_GREEN,
    Yellow = COLOR_YELLOW,
    Blue = COLOR_BLUE,
    Magenta = COLOR_MAGENTA,
    Cyan = COLOR_CYAN,
    White = COLOR_WHITE
};

constexpr uint16_t NUM_COLORS = 8;
constexpr Color Colors[NUM_COLORS] = {
    Color::Black,
    Color::Red,
    Color::Green,
    Color::Yellow,
    Color::Blue,
    Color::Magenta,
    Color::Cyan,
    Color::White
};

struct Pixel
{
    Color bgColor = Color::Black;
    Color chColor = Color::White;

    Vector2Int pos;
    chtype ch;

    Pixel(Vector2Int position, chtype character)
        : pos(position), ch(character)
    {

    }
};
