#pragma once
#include <vector>

using namespace std;



class MazeGenerator
{
public:
	MazeGenerator(int mapSize, int numExits) {
		map = vector<vector<char>>(mapSize, vector<char>(mapSize, ' '));
		this->mapSize = mapSize;
		this->numExits = numExits;
	}

	void printMaze();
	void createMaze();
	void createCorridors(int bisectRow, int bisectPoint, int stop);
	vector<int> createVerticalWall(int row, int point);
	vector<int> createHorizontalWall(int row, int point);
	
	enum Direction {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	};

	vector< vector<char>> map;
	int mapSize;
	int numExits;
	int horizontalOrVert;
};

