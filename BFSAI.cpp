#include "pch.h"
#include "BFSAI.h"

#include "Maze.h"

std::vector<Point> BFSAI::FindPath() {
    std::vector<Point> points;
    
    bool found[Maze::size][Maze::size] = { false };
    Point parent[Maze::size][Maze::size];
    std::queue<Point> q;

    q.emplace(posY, posX);
    found[posY][posX] = true;
    parent[posY][posX] = Point(posY, posX);

    while (!q.empty()) {
        const auto now = q.front();
        q.pop();

        for (int dir = Dir::Up; dir <= Dir::Left; ++dir) {
            auto nextX = now.x + xByDir[dir];
            auto nextY = now.y + yByDir[dir];
            if (Maze::GetInstance().PlayerCanGo(nextX, nextY) && !found[nextY][nextX]) {
                q.emplace(nextY, nextX);
                found[nextY][nextX] = true;
                parent[nextY][nextX] = Point(now.y, now.x);
            }
        }
    }

    auto x = Maze::destX;
    auto y = Maze::destY;
    while (parent[y][x].y != y || parent[y][x].x != x) {
        points.emplace_back(Point(y, x));

        const auto& point = parent[y][x];
        y = point.y;
        x = point.x;
    }

    points.emplace_back(Point(y, x));

    return points;
}
