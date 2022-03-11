//#include "pch.h"
//#include "PathFindingAI.h"
//
//enum Dir : int {
//    Up = 0,
//    Right,
//    Down,
//    Left,
//    // Max Except AStar
//    Up_Left,
//    Down_Left,
//    Down_Right,
//    Up_Right,
//    Max
//};
//
//const int xByDir[Dir::Max] = { 0, 1, 0, -1, -1, -1, 1, 1 };
//const int yByDir[Dir::Max] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//
//
//void RightHandAI::FindPath() {
//    int dir = Dir::Up;
//    _points.emplace_back(posY, posX);
//
//    while (posY != Maze::destY || posX != Maze::destX) {
//        if (_maze.PlayerCanGo(posX + xByDir[(dir + 1) % 4], posY + yByDir[(dir + 1) % 4])) {
//            dir = (dir + 1) % 4;
//
//            posX += xByDir[dir];
//            posY += yByDir[dir];
//        }
//        else if (_maze.PlayerCanGo(posX + xByDir[dir], posY + yByDir[dir])) {
//            posX += xByDir[dir];
//            posY += yByDir[dir];
//        }
//        else {
//            dir = (dir - 1 + 4) % 4;
//        }
//        _points.emplace_back(posY, posX);
//    }
//}
//
//bool found[Maze::size][Maze::size] = { };  // 여기가 아닌거같은데..?
//bool AlreadyFound(int x, int y) {
//    if (0 > x || 0 > y || Maze::size <= x || Maze::size <= y) {
//        return true;    // visited로 처리
//    }
//
//    return found[y][x];
//}
//
//void BFSAI::FindPath() {
//    // init for bfs
//    for (int y = 0; y < Maze::size; ++y) {
//        for (int x = 0; x < Maze::size; ++x) {
//            found[y][x] = false;
//        }
//    }
//
//    std::queue<Point> q;
//    q.push(Point(posY, posX));
//
//    Point parent[Maze::size][Maze::size];
//
//    found[posY][posX] = true;
//    parent[posY][posX] = Point(posY, posX);
//
//    while (!q.empty()) {
//        auto now = q.front();
//        q.pop();
//
//        for (int dir = Dir::Up; dir < Dir::Max; ++dir) {
//            auto nextX = now.x + xByDir[dir];
//            auto nextY = now.y + yByDir[dir];
//            if (_maze.PlayerCanGo(nextX, nextY)
//                && !AlreadyFound(nextX, nextY)) {
//                q.push(Point(nextY, nextX));
//                found[nextY][nextX] = true;
//
//                parent[nextY][nextX] = Point(now.y, now.x);
//            }
//        }
//    }
//
//    auto y = Maze::destY;
//    auto x = Maze::destX;
//    while (parent[y][x].y != y || parent[y][x].x != x) {
//        _points.emplace_back(Point(y, x));
//
//        y = parent[y][x].y;
//        x = parent[y][x].x;
//    }
//
//    _points.emplace_back(Point(y, x));
//}
//
//struct PQNode {
//public:
//    int F;
//    int G;
//    int Y;
//    int X;
//
//    bool operator<(const PQNode node) const {
//        return F > node.F;
//    }
//};
//
//void AStarAI::FindPath() {
//    // point(F) = G + H. 작을 수록 유리
//	// G : 시작지점에서 해당 좌표까지의 비용
//	// H : 목적지에서 얼마나 가까운지
//
//    const int cost[Dir::Max] = { 10, 10, 10, 10, 14, 14, 14, 14 };
//
//    // visited
//    bool closed[Maze::size][Maze::size];
//    int open[Maze::size][Maze::size] = { 0 };
//
//    // initialize array
//    for (int y = 0; y < Maze::size; ++y) {
//        for (int x = 0; x < Maze::size; ++x) {
//            closed[y][x] = false;
//            open[y][x] = INT_MAX;
//        }
//    }
//
//    Point parent[Maze::size][Maze::size] = { Point(0, 0) };
//    std::priority_queue<PQNode> queue;
//
//    open[posY][posX] = /*10 **/ (abs(Maze::destY - posY) + abs(Maze::destX - posX));
//    parent[posY][posX] = Point(posY, posX);
//    queue.push({ open[posY][posX], 0, posY, posX });
//
//    while (!queue.empty()) {
//        auto node = queue.top();
//        queue.pop();
//
//        closed[node.Y][node.X] = true;
//
//        if (Maze::destY == node.Y && Maze::destX == node.X) {
//            break;
//        }
//
//        for (int dir = Dir::Up; dir < Dir::Max; ++dir) {
//            const auto nextX = node.X + xByDir[dir];
//            const auto nextY = node.Y + yByDir[dir];
//            if (!_maze.PlayerCanGo(nextX, nextY)) {
//                continue;
//            }
//
//            if (closed[nextY][nextX]) {
//                continue;
//            }
//
//            int g = node.G + cost[dir];
//            int h = /*10 **/ (abs(Maze::destY - nextY) + abs(Maze::destX - nextX));
//            if (open[nextY][nextX] < g + h) {
//                continue;
//            }
//
//            open[nextY][nextX] = g + h;
//            parent[nextY][nextX] = Point(node.Y, node.X);
//            queue.push({ g + h, g, nextY, nextX });
//        }
//    }
//
//    auto y = Maze::destY;
//    auto x = Maze::destX;
//    while (parent[y][x].y != y || parent[y][x].x != x) {
//        _points.emplace_back(Point(y, x));
//
//        const auto parentPair = parent[y][x];
//        y = parent[y][x].y;
//        x = parent[y][x].x;
//    }
//
//    _points.emplace_back(Point(y, x));
//}
