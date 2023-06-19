#pragma once
#include <set>
#include <map>
#include "Vector2Int.h"
#include "Wall.h"

class Gate : public Wall
{
    std::map<Vector2Int, Vector2Int, UniqueVectorCompareator> enterExit;
    Wall* original;

public:
    Gate* exit = nullptr;

    ~Gate();
    Gate(Wall* wall, const std::set<Vector2Int, UniqueVectorCompareator>& opened);

    bool isGate() const final;

    // 게이트를 통해 나오는 좌표와 방향을 리턴
    std::pair<Vector2Int, Vector2Int> getExit(Vector2Int enterDirection) const;
};
