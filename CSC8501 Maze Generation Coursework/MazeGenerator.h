#pragma once
#include <vector>

using namespace std;



class MazeGenerator
{
public:
	enum Direction {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	};

	MazeGenerator(int mapSize, int numExits) {
		map = vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
		this->mapSize = mapSize;
		this->numExits = numExits;
	}

	void printMaze();
	void createMaze();
	void createCorridors(int row, int column);
	void removeOuterWalls();
	bool isValidExit(int row, int column, Direction dir);
	bool checkNeighbourTiles(int row, int column, Direction dir);
	vector<int> getNewDirection();
	

	vector< vector<char>> map;
	int mapSize;
	int numExits;
	enum Direction direction;
	
};

