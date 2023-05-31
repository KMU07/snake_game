#pragma once
#include <curses.h>

struct Pixel
{
    chtype ch;
    uint16_t x, y;
};
