#pragma once

#include "PathFindingAI.h"

class AStarAI : public PathFindingAI {
public:
	std::vector<Point> FindPath() override;
};
