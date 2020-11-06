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

	struct Positions {
		int row;
		int column;
	};
	struct AStarNode {
		int g; //number of steps from point starting position to current position.
		int h; // number of steps from current position to destination.
		AStarNode* parentNode; //stores previous node.


		//current position (row is x and y is column)
		Positions pos;

		int f; //sum of g and h
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
	void createCorridors(Positions pos);
	void removeOuterWalls();
	bool isValidExit(Positions exit, Direction dir);
	bool checkNeighbourTiles(Positions pos, Direction dir);
	void saveMaze(string filename);
	void carveCentralRoom();
	void assignExits();
	bool readMazeFile(string filename);
	vector<int> getNewDirection();

	//returns nodes in every cardinal direction if they exist/are allowed to be used to create a path.
	vector<AStarNode*> getAdjacentNodes(AStarNode* node, Positions destination);
	int distanceToDestination(Positions currentPosition, Positions destination);
	AStarNode* initialiseNode(Positions pos, Positions destination, AStarNode* parentNode);
	void findShortestPath(Positions pos, Positions exit);
	AStarNode* findSmallestFValue(vector<AStarNode*> evaluationList);
	bool containsPosition(vector<AStarNode*> closedList, Positions destinaion);
	void createFinalPath(AStarNode* destinationNode);
	AStarNode* initialiseStartingNode(Positions pos, Positions exit);
	void eraseListPointers(vector<AStarNode*> evaluationList, vector<AStarNode*> closedPath);

	vector< vector<char>> map;
	vector<Positions> exits;
	int mapSize;
	int numExits;
	enum Direction direction;

	Positions startingPosition;
	
};

