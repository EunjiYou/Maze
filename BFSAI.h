#pragma once

#include "PathFindingAI.h"

class BFSAI : public PathFindingAI {
public:
	std::vector<Point> FindPath() override;
};
