#include <iostream>
#include <exception>
#include "SnakeGame.h"

int main()
{
    try
    {
        SnakeGame snakeGame;
        snakeGame.run();
    }
    catch (std::exception e)
    {
        std::cerr << e.what();
    }

    return 0;
}
