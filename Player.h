#pragma once

#include "PathFindingAI.h"

enum class PathFindingType {
    RightHand,
    BFS,
    AStar
};

class Player
{
public:
	~Player();

    void Initialize(PathFindingType type);
    void Update();

    int posX = 1;
    int posY = 1;

    PathFindingAI* pathFindingAI;

private:
    std::vector<Point> _points;
};
