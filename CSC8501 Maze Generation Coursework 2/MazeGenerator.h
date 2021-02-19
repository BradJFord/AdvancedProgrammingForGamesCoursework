#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "Pathfinding.h"
#include "AStarNode.h"

using namespace std;

class MazeGenerator
{
public:

	struct Player {
		Positions pos;
		vector<AStarNode> path;

		bool deadlocked = false;

		int stationaryTurns = 0;

	};
	struct MazeResults {
		int fullyCompleteableCount = 0;
		int partialCompleteableCount = 0;
		int deadlockCount = 0;
	};


	MazeGenerator() {
		this->mapSize = 0;
		this->numExits = 0;
		this->numPlayers = 0;
		this->map = new vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
		this->playerProgressMap = new vector<vector<vector<char>>>;
	}

	MazeGenerator(int mapSize, int numExits, int numPlayers) {
		this->map = new vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
		this->mapSize = mapSize;
		this->numExits = numExits;
		this->numPlayers = numPlayers;
		this->playerProgressMap = new vector<vector<vector<char>>>;
	}

	void printMaze();
	void createMaze(bool createPlayerList);
	void createCorridors(Positions pos);
	void removeOuterWalls();
	bool isValidExit(Positions exit, Direction dir);
	bool checkNeighbourTiles(Positions pos, Direction dir);
	void saveMaze(string filename);
	void carveCentralRoom();
	void assignExits();
	bool readMazeFile(string filename);
	vector<int> getNewDirection();
	Direction determineExitDirection(Positions pos);

	void writeOptimalPathToMap(vector<AStarNode> path);
	void createPlayers();
	void movePlayers(Pathfinding path);
	void playerManager();
	bool validMove(Player player);
	bool finishingMove(Player player);
	void printPlayerProgress();
	void savePlayerProgress(string filename);
	bool readPlayerProgress(string filename);
	void deletePlayers();
	MazeResults hundredMazeGeneration(bool printAllMazes);


	vector< vector<char>>* map;
	vector<vector<vector<char>>>* playerProgressMap;
	vector<Positions> exits;
	vector<Player> players;
	vector<int> playerFinishingTurn;

	int mapSize;
	int numExits;
	int numPlayers;
	int turnCounter = 0;
	int deadlockedPlayers = 0;
	int finishedPlayers = 0;
	
	bool hundredMazes = false;

	MazeResults hundredMazeResults;
	enum Direction direction;

	Positions finishPosition;

};

