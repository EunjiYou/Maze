#include "pch.h"
#include "AStarAI.h"

#include "Maze.h"

struct PQNode {
public:
    int F;
    int G;
    int Y;
    int X;

    bool operator<(const PQNode& node) const {
        return F > node.F;
    }
};

std::vector<Point> AStarAI::FindPath() {
    std::vector<Point> points;

    constexpr int cost[Dir::Max] = { 10, 10, 10, 10, 14, 14, 14, 14 };

    std::priority_queue<PQNode> queue;
    Point parent[Maze::size][Maze::size] = { Point(0, 0) };
    bool closed[Maze::size][Maze::size] = { false };
    int open[Maze::size][Maze::size];
    for (int y = 0; y < Maze::size; ++y) {
        for (int x = 0; x < Maze::size; ++x) {
            open[y][x] = INT_MAX;
        }
    }

    open[posY][posX] = abs(Maze::destY - posY) + abs(Maze::destX - posX);
    parent[posY][posX] = Point(posY, posX);
    queue.push({ open[posY][posX], 0, posY, posX });

    while (!queue.empty()) {
        const auto node = queue.top();
        queue.pop();

        closed[node.Y][node.X] = true;

        if (Maze::destY == node.Y && Maze::destX == node.X) {
            break;
        }

        for (int dir = Dir::Up; dir < Dir::Max; ++dir) {
            const auto nextX = node.X + xByDir[dir];
            const auto nextY = node.Y + yByDir[dir];
            if (!Maze::GetInstance().PlayerCanGo(nextX, nextY)) {
                continue;
            }

            if (closed[nextY][nextX]) {
                continue;
            }

            int g = node.G + cost[dir];
            int h = abs(Maze::destY - nextY) + abs(Maze::destX - nextX);
            if (open[nextY][nextX] < g + h) {
                continue;
            }

            open[nextY][nextX] = g + h;
            parent[nextY][nextX] = Point(node.Y, node.X);
            queue.push({ g + h, g, nextY, nextX });
        }
    }

    auto y = Maze::destY;
    auto x = Maze::destX;
    while (parent[y][x].y != y || parent[y][x].x != x) {
        points.emplace_back(Point(y, x));

        const auto& point = parent[y][x];
        y = point.y;
        x = point.x;
    }

    points.emplace_back(Point(y, x));

    return points;
}