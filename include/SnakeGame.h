#pragma once
#include <chrono>
#include <vector>
#include <set>
#include "Game.h"
#include "GameObject.h"
#include "Vector2Int.h"
#include "Booster.h"
#include "Snake.h"
#include "Wall.h"
#include "SingleBlink.h"
#include "Gate.h"
#include "ScoreBoard.h"
#include "Mission.h"
#include "GameOverBoard.h"
using namespace std::chrono_literals;

class SnakeGame : public Game
{
    static constexpr auto GATE_MOVE_INTERVAL = 8500ms;
    static constexpr uint16_t MAX_LEVEL = 2;

    uint16_t gameLevel = 0;
    SnakeStatus status;

    std::map<Wall*, std::set<Vector2Int, UniqueVectorCompareator>> wallOpenedDirs;
    size_t width, height;

    GameOverBoard* gameOverInfo = nullptr;
    ScoreBoard scoreBoard;
    Mission mission;

    std::vector<Wall*> walls;
    Gate* gate1 = nullptr;
    Gate* gate2 = nullptr;

    SingleBlink* apple = nullptr;
    SingleBlink* poison = nullptr;
    Booster* booster = nullptr;
    Snake* snake = nullptr;

    Wall* getRandomWall();
    std::pair<Wall*, Wall*> getRandomWallPair();

public:
    ~SnakeGame();
    SnakeGame();

    Vector2Int useRandEmptyPos();

    void loadNextLevel();

    void update() final;
};
