#include <curses.h>
#include <cassert>
#include <deque>
#include "GameObject.h"
#include "GameEngine.h"

GameEngine::GameEngine()
{
    // Initialize curses
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    cbreak();
    noecho();
    start_color();

    // Initialize all possible color pairs
    uint16_t colorPairIndex = 1;

    for (uint16_t bgColor = 0; bgColor < NUM_COLORS; bgColor++)
    {
        for (uint16_t chColor = 0; chColor < NUM_COLORS; chColor++)
        {
            colorMap[{Colors[bgColor], Colors[chColor]}] = colorPairIndex;
            init_pair(colorPairIndex, Colors[bgColor], Colors[chColor]);
            colorPairIndex++;
        }
    }
}

GameEngine::~GameEngine()
{
    endwin();
}

GameEngine& GameEngine::getInstance()
{
    static GameEngine instance;
    return instance;
}

void GameEngine::registObject(GameObject* const obj)
{
    auto insertIter = objects.end();

    // Find the iterator where this object should be inserted by upper bound.
    for (auto itr = objects.begin(); itr != objects.end(); ++itr)
    {
        if ((*itr)->processOrder > obj->processOrder)
        {
            insertIter = itr;
            break;
        }
    }

    objects.insert(insertIter, obj);
}

void GameEngine::deregistObject(GameObject* const obj)
{
    for (auto itr = objects.begin(); itr != objects.end(); ++itr)
    {
        if (*itr == obj)
        {
            objects.erase(itr);
            break;
        }
    }
}

void GameEngine::processCollision()
{
    // To do: Implement in progress...
    // 충돌을 확인하는 여러 방법 중 최대한 성능이 괜찮은 방법으로 작성하겠습니다.
}

void GameEngine::updateAll()
{
    for (GameObject* obj : objects)
    {
        if (!obj->enabled)
            continue;

        obj->update();
    }
}

void GameEngine::render()
{
    static auto prevRenderTime = std::chrono::system_clock::now();
    const auto now = std::chrono::system_clock::now();

    if (prevRenderTime + renderDelay >= now)
        return;
    prevRenderTime = now;

    // Set default color
    uint16_t defaultColor = colorMap.size() + 1;

    init_pair(defaultColor, defaultbgColor, defaultChColor);
    bkgd(COLOR_PAIR(defaultColor));

    // Render all objects
    uint16_t prevOrder = 0;

    for (GameObject* const nowObj : objects)
    {
        assert(prevOrder <= nowObj->processOrder);
        prevOrder = nowObj->processOrder;

        if (!nowObj->enabled)
            continue;

        for (Pixel& p : nowObj->pixels)
        {
            if (p.pos.x < 0 || p.pos.y < 0)
                continue;

            uint16_t colorPairIndex = colorMap[{p.bgColor, p.chColor}];

            attron(COLOR_PAIR(colorPairIndex));
            mvaddch(p.pos.y, p.pos.x, p.ch);
        }
    }

    // Set to default color and refresh
    attron(COLOR_PAIR(defaultColor));
    refresh();
}
