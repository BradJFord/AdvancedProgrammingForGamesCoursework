#pragma once
#include "MazeGenerator.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;
class UserInterface {
	public:
		UserInterface() {}

		void generateRandomMaze();
		void readMaze();

	private:
		void printOptimalPaths();
		void saveMaze();

		MazeGenerator maze;
};
