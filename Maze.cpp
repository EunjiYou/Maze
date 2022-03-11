#include "pch.h"
#include "Maze.h"

#include "Player.h"


void Maze::GenerateBySideWinder() {
    srand(static_cast<unsigned>(time(nullptr)));
    
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (0 == y % 2 || 0 == x % 2) {
                _maze[y][x] = TileType::Wall;
            }
            else {
                _maze[y][x] = TileType::Empty;
            }
        }
    }

    int sideCounter;
    for (int y = 0; y < size; ++y) {
        sideCounter = 1;
        for (int x = 0; x < size; ++x) {
            if (0 == y % 2 || 0 == x % 2) {
                continue;
            }

            if (size - 2 == y && size - 2 == x) {
                continue;
            }

            if (size - 2 == y) {
                _maze[y][x + 1] = TileType::Empty;
                continue;
            }

            if (size - 2 == x) {
                _maze[y + 1][x] = TileType::Empty;
                continue;
            }

            if (0 == rand() % 2) {
                ++sideCounter;
                _maze[y][x + 1] = TileType::Empty;
            }
            else {
                const int randomIdx = rand() % sideCounter;
                _maze[y + 1][x - (2 * randomIdx)] = TileType::Empty;
                sideCounter = 1;
            }
        }
    }
}

Maze::Maze() {
    GenerateBySideWinder();
}

void Maze::AddPlayer(Player& player) {
    _players.emplace_back(&player);
}

bool Maze::PlayerCanGo(int x, int y) {
    if(0 > x || size <= x || 0 > y || size <= y) {
        return false;
    }

    return TileType::Empty == _maze[y][x];
}

void Maze::ShowMaze() {
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            bool playerInTile = false;
        	for (const auto player : _players) {
                if (x == player->posX && y == player->posY) {
                    std::cout << "б▄";
                    playerInTile = true;
                    break;
                }
            }

            if(playerInTile) {
                continue;
            }

        	if (TileType::Wall == _maze[y][x]) {
                std::cout << "бс";
            }
            else {
                std::cout << "бр";
            }
        }

        std::cout << "\n";
    }
}
