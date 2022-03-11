#pragma once

#include "PathFindingAI.h"

class RightHandAI : public PathFindingAI {
public:
	std::vector<Point> FindPath() override;
};
