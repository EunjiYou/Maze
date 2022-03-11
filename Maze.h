#pragma once

class Player;

enum class TileType : int {
    Empty,
    Wall
};

class Maze {
public:
    Maze(const Maze&) = delete;
    Maze operator=(const Maze&) = delete;

	static Maze& GetInstance() {
        static Maze instance;
    	return instance;
    }

    void ShowMaze();
    void AddPlayer(Player& player);
    bool PlayerCanGo(int x, int y);

    static constexpr int size = 25;
    static constexpr int destX = 23;
    static constexpr int destY = 23;

private:
    Maze();

    std::vector<Player*> _players;
    TileType _maze[size][size];

    void GenerateBySideWinder();
};
