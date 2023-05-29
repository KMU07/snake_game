#pragma once
#include <curses.h>
#include <cstdint>

struct Pixel
{
    chtype ch;
    uint16_t x, y;
};
