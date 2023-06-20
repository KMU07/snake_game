#include <curses.h>
#include <cassert>
#include <deque>
#include <set>
#include "GameObject.h"
#include "GameEngine.h"

GameEngine::GameEngine()
{
    // Initialize curses
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
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
            init_pair(colorPairIndex, Colors[chColor], Colors[bgColor]);
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
    std::map<Vector2Int, std::vector<GameObject*>, UniqueVectorCompareator> m;

    for (GameObject* obj : objects)
    {
        if (!obj->enabled || !obj->isCollisionable())
            continue;

        for (Pixel& pixel : obj->pixels)
            m[pixel.pos].push_back(obj);
    }

    std::set<std::tuple<uint16_t, GameObject*, GameObject*>> collisioned;

    // All GameObjects located in the same position are determined to collide.
    for (auto& [_, objs] : m)
    {
        for (size_t i = 0; i < objs.size(); i++)
        {
            for (size_t j = 0; j < objs.size(); j++)
            {
                if (i == j)
                    continue;
                collisioned.emplace(objs[i]->processOrder, objs[i], objs[j]);
            }
        }
    }

    // Call onCollision events
    for (auto& [_, obj1, obj2] : collisioned)
    {
        if (!obj1->enabled)
            continue;
        obj1->onCollision(obj2);
    }
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

    // Clear the screen
    clear();

    // Set default color
    uint16_t defaultColor = colorMap.size() + 1;

    init_pair(defaultColor, defaultChColor, defaultbgColor);
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

            const uint16_t colorPairIndex = colorMap[{p.bgColor, p.chColor}];
            attron(COLOR_PAIR(colorPairIndex));

            const std::string s(std::format("{}", p.ch));
            mvaddstr(p.pos.y, p.pos.x, s.c_str());
        }
    }

    refresh();
}
