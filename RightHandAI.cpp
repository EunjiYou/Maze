#include "pch.h"
#include "RightHandAI.h"

#include "Maze.h"


std::vector<Point> RightHandAI::FindPath() {
    std::vector<Point> points;

	int dir = Dir::Up;
    points.emplace_back(posY, posX);

    while (posY != Maze::destY || posX != Maze::destX) {
        if (Maze::GetInstance().PlayerCanGo(posX + xByDir[(dir + 1) % 4], posY + yByDir[(dir + 1) % 4])) {
            dir = (dir + 1) % 4;

            posX += xByDir[dir];
            posY += yByDir[dir];
            points.emplace_back(posY, posX);
        }
        else if (Maze::GetInstance().PlayerCanGo(posX + xByDir[dir], posY + yByDir[dir])) {
            posX += xByDir[dir];
            posY += yByDir[dir];
            points.emplace_back(posY, posX);
        }
        else {
            dir = (dir - 1 + 4) % 4;
        }
    }
    
    std::ranges::reverse(points);
    return points;
}
