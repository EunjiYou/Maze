#include "pch.h"

#include <Windows.h>
#include "Maze.h"
#include "Player.h"


void setCursor(short x, short y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
}

int main() {
	Player player;
	player.Initialize(PathFindingType::RightHand);
	Maze::GetInstance().AddPlayer(player);

	Player player2;
	player2.Initialize(PathFindingType::BFS);
	Maze::GetInstance().AddPlayer(player2);

	Player player3;
	player3.Initialize(PathFindingType::AStar);
	Maze::GetInstance().AddPlayer(player3);

	while (true) {
		setCursor(0, 0);
		
		player.Update();
		player2.Update();
		player3.Update();

		Maze::GetInstance().ShowMaze();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}