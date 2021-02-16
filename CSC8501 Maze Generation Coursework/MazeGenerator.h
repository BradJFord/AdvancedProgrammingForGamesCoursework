#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "AStarNode.h"

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

	MazeGenerator() {
		this->mapSize = 0;
		this->numExits = 0;
		this->map = new vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
	}
	MazeGenerator(int mapSize, int numExits) {
		this->map = new vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
		this->mapSize = mapSize;
		this->numExits = numExits;
	}

	void printMaze();
	void createMaze();
	void createCorridors(Positions pos);
	void removeOuterWalls();
	bool isValidExit(Positions exit, Direction dir);
	bool checkNeighbourTiles(Positions pos, Direction dir);
	void saveMaze(string filename);
	void carveCentralRoom();
	void assignExits();
	bool readMazeFile(string filename);
	vector<int> getNewDirection();


	vector< vector<char>>* map;
	vector<Positions> exits;
	int mapSize;
	int numExits;
	enum Direction direction;

	Positions startingPosition;
	
};

