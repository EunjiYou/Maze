#pragma once

#include <vector>

struct Point {
	int y;
	int x;
};

enum Dir : int {
	Up = 0,
	Right,
	Down,
	Left,
	Up_Left,
	Down_Left,
	Down_Right,
	Up_Right,
	Max
};

constexpr int xByDir[Dir::Max] = { 0, 1, 0, -1, -1, -1, 1, 1 };
constexpr int yByDir[Dir::Max] = { -1, 0, 1, 0, -1, 1, 1, -1 };

class PathFindingAI {
public:
	virtual std::vector<Point> FindPath() = 0;

protected:
	int posX = 1;
	int posY = 1;
};
