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

inline constexpr uint16_t NUM_COLORS = 8;
inline constexpr Color Colors[NUM_COLORS] = {
    Color::Black,
    Color::Red,
    Color::Green,
    Color::Yellow,
    Color::Blue,
    Color::Magenta,
    Color::Cyan,
    Color::White
};

// 2바이트 문자들 때문에 ch는 일단 string 타입이나,
// 의도대로 작동을 원한다면 문자 하나만 넣어야 함
struct Pixel
{
    Color bgColor = Color::Black;
    Color chColor = Color::White;

    Vector2Int pos;
    std::string ch = "O";
};
