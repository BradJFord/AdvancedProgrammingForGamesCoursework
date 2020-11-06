#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>

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

	struct AStarNode {
		int g; //number of steps from point starting position to current position.
		int h; // number of steps from current position to destination.
		AStarNode* parentNode; //stores previous node.


		//current position (row is x and y is column)
		int row;
		int column;

		int f; //sum of g and h
	};

	struct Positions {
		int row;
		int column;
	};
	MazeGenerator() {
		this->mapSize = 0;
		this->numExits = 0;
		this->map = vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
	}
	MazeGenerator(int mapSize, int numExits) {
		this->map = vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
		this->mapSize = mapSize;
		this->numExits = numExits;
	}

	void printMaze();
	void createMaze();
	void createCorridors(int row, int column);
	void removeOuterWalls();
	bool isValidExit(int row, int column, Direction dir);
	bool checkNeighbourTiles(int row, int column, Direction dir);
	void saveMaze();
	void readMazeFile(string filename);
	vector<int> getNewDirection();

	//returns nodes in every cardinal direction if they exist/are allowed to be used to create a path.
	vector<AStarNode*> getAdjacentNodes(AStarNode* node, int destinationRow, int destinationColumn);
	int distanceToDestination(int currentRow, int currentColumn,int destinationRow, int destinationColumn);
	AStarNode* initialiseNode(int row, int column, int destinationRow, int destinationColumn, AStarNode* parentNode);
	void findShortestPath(int row,int column, Positions exit);
	AStarNode* findSmallestFValue(vector<AStarNode*> evaluationList);
	bool endReached(vector<AStarNode*> closedList, int destinationRow, int destinationColumn);
	void createFinalPath(AStarNode* destinationNode);


	vector< vector<char>> map;
	vector<Positions> exits;
	int mapSize;
	int numExits;
	enum Direction direction;

	Positions startingPosition;

	//int exitRow;
	//int exitColumn;
	
};

