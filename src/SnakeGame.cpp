#include <fstream>
#include <string>
#include <random>
#include <set>
#include "Vector2Int.h"
#include "SnakeGame.h"
#include "Gate.h"

SnakeGame::~SnakeGame()
{
    delete apple;
    delete poison;
    delete booster;
    delete snake;
}

SnakeGame::SnakeGame()
    : scoreBoard(status), mission(status)
{
    resize_term(27, 50);
    this->loadNextLevel();
}

Wall* SnakeGame::getRandomWall()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::vector<Wall*> normalWalls;

    for (Wall* wall : walls)
    {
        if (wall->bounce || wall->immune || !wall->enabled)
            continue;
        normalWalls.push_back(wall);
    }

    // 벽이 1개도 안되면 nullptr를 반환하여 게이트 생성X
    if (normalWalls.empty())
        return nullptr;

    // 랜덤한 한 벽을 반환한다.
    std::uniform_int_distribution<std::size_t> dis(0, normalWalls.size() - 1);
    return normalWalls[dis(gen)];
}

std::pair<Wall*, Wall*> SnakeGame::getRandomWallPair()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // 이건 loadNextLevel 함수에서 할 수 있음!
    // 최적화 가능.
    std::vector<Wall*> normalWalls;

    for (Wall* wall : walls)
    {
        if (wall->bounce || wall->immune || !wall->enabled)
            continue;
        normalWalls.push_back(wall);
    }

    // 벽이 2개도 안되면 nullptr를 반환하여 게이트 생성X
    if (normalWalls.size() < 2)
        return { nullptr, nullptr };

    // 2개의 벽을 고른다.
    std::vector<Wall*> ret;

    std::sample(
        normalWalls.begin(),
        normalWalls.end(),
        std::back_inserter(ret),
        2, gen
    );

    return { ret[0], ret[1] };
}

Vector2Int SnakeGame::useRandEmptyPos()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // 오브젝트가 차지하는 모든 좌표를 집어넣음
    std::vector<Vector2Int> nonEmpty;

    if (apple != nullptr)
        nonEmpty.push_back(apple->pixels[0].pos);

    if (poison != nullptr)
        nonEmpty.push_back(poison->pixels[0].pos);

    if (booster != nullptr)
        nonEmpty.push_back(booster->pixels[0].pos);

    if (snake != nullptr)
        for (Pixel& p : snake->pixels)
            nonEmpty.push_back(p.pos);

    for (Wall* wall : walls)
        nonEmpty.push_back(wall->pixels[0].pos);

    // 빈 공간을 알아낸다.
    std::vector<Vector2Int> empty;

    for (uint16_t y = 0; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            Vector2Int pos(x, y);

            if (std::find(nonEmpty.begin(), nonEmpty.end(), pos) == nonEmpty.end())
                empty.push_back(pos);
        }
    }

    // 빈 공간 중 랜덤한 한 좌표를 반환한다.
    std::uniform_int_distribution<std::size_t> dis(0, empty.size() - 1);
    return empty[dis(gen)];
}

void SnakeGame::loadNextLevel()
{
    delete apple;
    apple = nullptr;

    delete poison;
    poison = nullptr;

    delete booster;
    booster = nullptr;

    delete snake;
    snake = nullptr;

    wallOpenedDirs.clear();

    while (!walls.empty())
    {
        delete walls.back();
        walls.pop_back();
    }

    if (gameLevel != MAX_LEVEL)
        gameLevel++;

    const std::string fileName = std::format("map_{}.sgmap", gameLevel);
    std::ifstream in(fileName);

    // Set boards and get goals from file
    status.appleGets = 0;
    status.boosterGets = 0;
    status.currentLength = 0;
    status.gatePass = 0;
    status.poisonGets = 0;
    status.wallBounced = 0;

    in >> status.maxLength;
    in >> mission.wallBounceGoal;
    in >> mission.boosterGoal;
    in >> mission.appleGoal;
    in >> mission.poisonGoal;
    in >> mission.gatePassGoal;
    in.ignore();

    // Read map from file
    std::vector<std::string> lines;

    for (std::string line; std::getline(in, line);)
        lines.push_back(line);

    width = lines[0].length();
    height = lines.size();

    // Set board's position
    scoreBoard.boxX = width + 2;
    scoreBoard.boxY = 0;
    mission.boxX = width + 2;
    mission.boxY = scoreBoard.height + 2;

    std::vector<Vector2Int> body;
    Vector2Int head;

    // Set information of objects
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            switch (lines[y][x])
            {
            case '1':
                // Normal wall
                walls.push_back(new Wall(Vector2Int(x, y)));
                break;
            case '2':
                // Immune wall
                walls.emplace_back(new Wall(Vector2Int(x, y), true));
                break;
            case '3':
                // Snake head
                head.x = x;
                head.y = y;
                break;
            case '4':
                // Snake body
                body.emplace_back(x, y);
                break;
            case '5':
                // Bounce wall
                walls.emplace_back(new Wall(Vector2Int(x, y), false, true));
                break;
            }
        }
    }

    const std::vector<Vector2Int> verticalAndHorizontal = {
        Vector2Int::up,
        Vector2Int::down,
        Vector2Int::left,
        Vector2Int::right
    };

    // 나중에 벽에 게이트를 만들 때 어느 방향이 열려있는지 알기 위해 미리 정보를 저장한다.
    for (Wall* wall : walls)
    {
        if (wall->bounce || wall->immune || !wall->enabled)
            continue;

        const Vector2Int wallPos = wall->pixels[0].pos;

        std::set<Vector2Int, UniqueVectorCompareator> openedDirs;
        for (uint8_t d = 0; d < 4; d++)
        {
            const Vector2Int dir = verticalAndHorizontal[d];
            const Vector2Int sidePos = wallPos + dir;

            if (sidePos.x < 0 || sidePos.x >= lines[0].length() ||
                sidePos.y < 0 || sidePos.y >= lines.size() ||
                lines[sidePos.y][sidePos.x] != '0')
                continue;

            openedDirs.insert(dir);
        }

        wallOpenedDirs[wall] = openedDirs;
    }

    // Sort body by distance with head and reset snake
    Vector2Int toHead0 = body[0] - head;
    Vector2Int toHead1 = body[1] - head;

    if (toHead0.manhattan() > toHead1.manhattan())
        std::swap(toHead0, toHead1);

    snake = new Snake(status, head, body[0], body[1]);
    apple = new SingleBlink("Apple", *this, Color::Green, 9s);
    poison = new SingleBlink("Poison", *this, Color::Red, 8s);
    booster = new Booster(*this);
}

void SnakeGame::update()
{
    static auto lastGateMove = std::chrono::system_clock::now() - GATE_MOVE_INTERVAL;
    const auto now = std::chrono::system_clock::now();

    // 게임 오버 체크
    if (snake->isDead())
    {
        if (gameOverInfo == nullptr)
            gameOverInfo = new GameOverBoard(snake->getReasonOfDeath());

        scoreBoard.enabled = false;
        mission.enabled = false;

        apple->enabled = false;
        poison->enabled = false;
        booster->enabled = false;
        snake->enabled = false;

        if (gate1 != nullptr)
            gate1->enabled = false;
        if (gate2 != nullptr)
            gate2->enabled = false;

        while (!walls.empty())
        {
            delete walls.back();
            walls.pop_back();
        }
    }

    // status.currentLength 동기화
    status.currentLength = snake->getBodyLength();

    // 미션 달성 검사 & 레벨 변경
    if (mission.allSuccess())
    {
        this->loadNextLevel();
        lastGateMove = std::chrono::system_clock::now() - GATE_MOVE_INTERVAL;
        return;
    }

    // 게이트 변경
    if (walls.size() > 2 && lastGateMove + GATE_MOVE_INTERVAL <= now)
    {
        delete gate1;
        gate1 = nullptr;

        delete gate2;
        gate2 = nullptr;

        auto [wall1, wall2] = getRandomWallPair();

        gate1 = new Gate(wall1, wallOpenedDirs[wall1]);
        gate2 = new Gate(wall2, wallOpenedDirs[wall2]);

        gate1->exit = gate2;
        gate2->exit = gate1;

        lastGateMove += GATE_MOVE_INTERVAL;
    }
}
