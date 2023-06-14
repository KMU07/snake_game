#pragma once
#include <chrono>
#include <list>
#include <map>
#include "Pixel.h"
using namespace std::chrono_literals;

class GameObject;

// This class is singleton pattern.
class GameEngine final
{
    std::map<std::pair<Color, Color>, uint16_t> colorMap;

    // objects must always be sorted.
    std::list<GameObject*> objects;

    GameEngine();

public:
    std::chrono::milliseconds renderDelay = 1ms;
    Color defaultbgColor = Color::Black;
    Color defaultChColor = Color::White;

    ~GameEngine();

    static GameEngine& getInstance();

    void registObject(GameObject* const obj);
    void deregistObject(GameObject* const obj);

    // Process collisions of enabled GameObjects.
    void processCollision();

    // Call all enabled GameObjects's update mehtod.
    void updateAll();

    // Render all registed objects.
    void render();

    // You can't use copy constructor on singleton class!
    GameEngine(const GameEngine&) = delete;
    // You can't use copy operator on singleton class!
    GameEngine& operator=(const GameEngine&) = delete;
};
