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
	void printMaze(vector< vector<char>> map);
	vector<vector<char>> carveMaze(vector<vector<char>> map , int numExits);
};

