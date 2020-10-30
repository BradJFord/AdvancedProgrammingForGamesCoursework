#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "MazeGenerator.h"


void MazeGenerator::printMaze(vector< vector<char>> map) {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			cout << map[i][j] << " ";
			if (j == map[0].size() - 1) {
				cout << endl;
			}
		}
	}
}
vector<vector<char>> MazeGenerator::carveMaze(vector<vector<char>>map, int numExits) {
	//carve the central 3x3 starting room
	for (int i = -2; i < 1; i++) {
		for (int j = -2; j < 1; j++) {
			map[(map.size() / 2) + i][(map[0].size() / 2) + j] = ' ';
		}
	}

	map[(map.size() / 2) - 1][(map[0].size() / 2) - 1] = 'S';

	//assign exits
	for (int i = 0; i < numExits;i++) {
		enum Direction direction = static_cast<Direction>(rand() % 4);
		
		int x;
		int y;
		
		if (direction == Direction::UP) {
			x = 0;
			y = rand() % map[0].size();
		}else if (direction == Direction::LEFT) {
			x = rand() % map.size();
			y = 0;
		}
		else if (direction == Direction::RIGHT) {
			x = map[0].size()-1;
			y = rand() % map.size();
		}
		else if (direction == Direction::DOWN) {
			x = rand() % map[0].size();
			y = map.size()-1;
		}
		map[x][y] = 'E';
	}

	


	return map;

}
int main() {
	srand(time(NULL));
	int mapSize;
	int numExits;
	cout << "Please enter a map size, (e.g. map size of 20 will result in 20x20 map)" << endl;
	cin >> mapSize;
	cout << "Please the amount of exits you would like." << endl;
	cin >> numExits;
	vector< vector<char>> map(mapSize, vector<char>(mapSize, 'x'));
	MazeGenerator maze;
	//maze.printMaze(map);
	map = maze.carveMaze(map,numExits);
	maze.printMaze(map);
	return 0;
}