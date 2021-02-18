#pragma once
#include "MazeGenerator.h"
#include <iostream>
#include <time.h>
#include <string>

class UserInterface {

	public:
		UserInterface() {}

		MazeGenerator generateRandomMaze();
		void readMaze();

		bool playGame();
		void readPlayerProgressFile();
		void printProgress();
		void generateOneHundredMazes();

		MazeGenerator getMaze() {
			return *maze;
		}

	private:

		bool printOptimalPaths(bool playerFlag);
		void saveMaze();
		bool generatePlayersOrNot();
		void playersDetected();
		void saveProgress();
		void displayInformation(vector<MazeGenerator::MazeResults> results, int firstMapSize, int lastMapSize, int firstNumExitsPlayers, int secondNumExitsPlayers);

		MazeGenerator* maze;
};
