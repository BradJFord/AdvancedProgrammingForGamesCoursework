#include "UserInterface.h"
using namespace std;

bool UserInterface::playGame() {
	int option;
	bool validOption = false;
	while (!validOption) {
		cout << "Would you like the players to play the game?" << endl;
		cout << "1.Yes" << endl;
		cout << "2.No" << endl;
		cin >> option;

		if (option == 1) {
			validOption = true;
			return true;
		}
		else if (option == 2) {
			validOption = true;
			return false;
		}
		else {
			cout << "Please enter a valid option" << endl;
		}
	}
}

bool UserInterface::printOptimalPaths(bool playerFlag) {
	bool optionSelected = false;
	bool printedPath = false;
	if (playerFlag) {
		while (!optionSelected) {
			int option;
			cout << endl;
			cout << "Would you like to print the optimal paths from each player to the exit?" << endl;
			cout << "1. Yes" << endl;
			cout << "2. No" << endl;
			cin >> option;

			if (option == 1) {
				optionSelected = true;
				Pathfinding path(maze->map, maze->mapSize);
				for (int i = 0; i < maze->players.size(); i++) {
					maze->writeOptimalPathToMap(path.findShortestPath(maze->players.at(i).pos, maze->finishPosition));
				}
				maze->printMaze();
				printedPath = true;
			}
			else if (option == 2) {
				optionSelected = true;
				printedPath = false;

			}
			else {
				cout << "Please enter a valid option." << endl;
				cout << '/n' << endl;
			}
		}
	}
	else {
		int option;
		cout << endl;
		cout << "Would you like to print the optimal paths from the entrances to the exit?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cin >> option;

		if (option == 1) {
			optionSelected = true;
			Pathfinding path(maze->map, maze->mapSize);
			for (int i = 0; i < maze->exits.size(); i++) {
				maze->writeOptimalPathToMap(path.findShortestPath(maze->finishPosition, maze->exits.at(i)));
			}
			maze->printMaze();
		}
		else if (option == 2) {
			optionSelected = true;

		}
		else {
			cout << "Please enter a valid option." << endl;
			cout << '/n' << endl;
		}
	}
	return printedPath;
}


void UserInterface::saveMaze() {
	int option = 0;
	bool optionSelected = false;
	while (!optionSelected) {
		cout << "1. Save Maze To File" << endl;
		cout << "2. Back to main menu" << endl;

		cin >> option;

		if (option == 1) {
			string filename;
			cout << "Please enter a name for your file (without '.txt')" << endl;
			cin >> filename;
			maze->saveMaze(filename + ".txt");
			optionSelected = true;
		}
		else if (option == 2) {
			optionSelected = true;
		}
		else {
			cout << "Please enter a valid option." << endl;
			cout << '/n' << endl;
		}
	}
}


bool UserInterface::generatePlayersOrNot() {
	int option;
	bool validOption = false;
	while (!validOption) {
		cout << "Would you like to spawn players for this maze?" << endl;
		cout << "1.Yes" << endl;
		cout << "2.No" << endl;
		cin >> option;

		if (option == 1) {
			validOption = true;
			return true;
		}
		else if (option == 2) {
			validOption = true;
			return false;
		}
		else {
			cout << "Please enter a valid option." << endl;
		}
	}
}

MazeGenerator UserInterface::generateRandomMaze() {
	int mapSize;
	int numExitsPlayers = 0;
	int option;
	int numExits = 0;
	int numPlayers;
	bool validSize = false;
	bool playerFlag = false;
	while (!validSize) {
		cout << "Please enter a map size, between 20 and 100 (e.g. map size of 20 will result in 20x20 map)" << endl;
		cin >> mapSize;

		if (mapSize <= 100 && mapSize >= 20) {
			validSize = true;
		}
		else {
			cout << "Please enter a valid maze size." << endl;
		}
	}
	
	playerFlag = generatePlayersOrNot();

	if (playerFlag) {
		bool validExitPlayers = false;
		while (!validExitPlayers) {
			cout << "Please the amount of exits and players you would like. (15 exits max)" << endl;
			cin >> numExitsPlayers;

			if (numExitsPlayers > 0 && numExitsPlayers <= 15) {
				validExitPlayers = true;
				numExits = numExitsPlayers;
			}
			else {
				cout << "Please enter a valid number of exits/players." << endl;
			}
		}
	} 
	else {
		bool validExit = false;
		while (!validExit) {
			cout << "Please the amount of exits you would like. (15 exits max)" << endl;
			cin >> numExits;

			if (numExits > 0 && numExits <= 15) {
				validExit = true;
			}
			else {
				cout << "Please enter a valid number of exits." << endl;
			}
		}
	}
	maze = new MazeGenerator(mapSize, numExits, numExitsPlayers);
	maze->createMaze(playerFlag);
	maze->printMaze();
	

	if (!printOptimalPaths(playerFlag)){
		saveMaze();
	}

	return *maze;
}

void UserInterface::playersDetected() {
	int option;
	bool validOption = false;
	while (!validOption) {
		cout << "There were players detected in the file. Would you like to keep them or generate new players?" << endl;
		cout << "1.Generate new players" << endl;
		cout << "2.Keep current players" << endl;
		cin >> option;

		if (option == 1) {
			validOption = true;
			maze->deletePlayers();
			maze->createPlayers();
		}
		else if (option == 2) {
			validOption = true;
		}
		else {
			cout << "Please enter a valid option." << endl;
		}
	}
}

void UserInterface::readMaze() {
	bool validFile = false;
	while (!validFile) {
		cout << "Please enter the file you would like to read (without '.txt')" << endl;
		cout << "" << endl;
		string filename;
		cin >> filename;
		if (!maze->readMazeFile(filename + ".txt")) {
			int option = 0;
			bool optionSelected = false;
			while (!optionSelected) {
				cout << "1. Enter file name again." << endl;
				cout << "2. Exit back to main menu" << endl;
				cin >> option;

				if (option == 1) {
					optionSelected = true;
				}
				else if (option == 2) {
					validFile = true;
					optionSelected = true;
				}
				else {
					cout << "Please enter a valid option." << endl;
					cout << '/n' << endl;
				}

			}
		}
		else {
			validFile = true;
			if (maze->players.size()>0) {
				playersDetected();

			}
			maze->printMaze();

			MazeGenerator mazeCopy = getMaze();

			if (playGame()) {
				maze->playerManager();
				printProgress();
			}
		}
	}
}
void UserInterface::readPlayerProgressFile() {
	MazeGenerator maze;
	bool validFile = false;
	while (!validFile) {
		cout << "Please enter the player progress file you would like to read (without '.txt')" << endl;
		cout << "" << endl;
		string filename;
		cin >> filename;
		if (!maze.readPlayerProgress(filename + ".txt")) {
			int option = 0;
			bool optionSelected = false;
			while (!optionSelected) {
				cout << "1. Enter file name again." << endl;
				cout << "2. Exit back to main menu" << endl;
				cin >> option;

				if (option == 1) {
					optionSelected = true;
				}
				else if (option == 2) {
					validFile = true;
					optionSelected = true;
				}
				else {
					cout << "Please enter a valid option." << endl;
					cout << '/n' << endl;
				}

			}
		}
		else {
			validFile = true;
			maze.printPlayerProgress();
		}
	}
	
}

void UserInterface::saveProgress() {
	int option;
	bool validOption = false;
	string filename;
	while (!validOption) {
		cout << "Would you like to save player progress?" << endl;
		cout << "1.Yes" << endl;
		cout << "2.No" << endl;
		cin >> option;

		if (option == 1) {
			validOption = true;
			cout << "Please enter the name of the file you would like to save. (without '.txt')" << endl;
			cin >> filename;
			maze->savePlayerProgress(filename+".txt");
		}
		else if (option == 2) {
			validOption = true;
		}
		else {
			cout << "Please enter a valid option" << endl;
		}
	}
}
void UserInterface::printProgress() {
	int option;
	bool validOption = false;
	while (!validOption) {
		cout << "Would you like to print player progress?" << endl;
		cout << "1.Yes" << endl;
		cout << "2.No" << endl;
		cin >> option;

		if (option == 1) {
			validOption = true;
			maze->printPlayerProgress();
			saveProgress();
		}
		else if (option == 2) {
			validOption = true;
		}
		else {
			cout << "Please enter a valid option" << endl;
		}
	}
	
}
void UserInterface::displayInformation(vector<MazeGenerator::MazeResults> results, int firstMapSize, int lastMapSize, int firstNumExitsPlayers, int secondNumExitsPlayers) {
	int copyPlayerExit = firstNumExitsPlayers;
	for (int i = 0; i < results.size(); i++) {
		for (int j = firstNumExitsPlayers; j < secondNumExitsPlayers; j++) {
			cout << "Results for 100 Mazes of Size " << firstMapSize << " with " << j << " players." << endl;
			cout << "Completeable Mazes: " << results.at(i).fullyCompleteableCount << " Partially Completeable: " << results.at(i).partialCompleteableCount << " Deadlock Count: " << results.at(i).deadlockCount << endl;
		}
		firstNumExitsPlayers = copyPlayerExit;
	}
}


void UserInterface::generateOneHundredMazes() {
	int firstMapSize = 0;
	int lastMapSize = 0;
	int firstNumExitsPlayers = 0;
	int secondNumExitsPlayers = 0;
	int option;
	bool firstValidSize = false;
	bool secondValidSize = false;
	while (!firstValidSize) {
		cout << "Please enter a starting map size, between 20 and 100 (e.g. map size of 20 will result in 20x20 map)" << endl;
		cin >> firstMapSize;

		if (firstMapSize <= 100 && firstMapSize >= 20) {
			firstValidSize = true;
		}
		else {
			cout << "Please enter a valid maze size." << endl;
		}
	}
	while (!secondValidSize) {
		cout << "Please enter a final map size, between the previous value entered and 100 (e.g. map size of 20 will result in 20x20 map)" << endl;
		cin >> lastMapSize;

		if (lastMapSize <= 100 && lastMapSize > firstMapSize) {
			secondValidSize = true;
		}
		else {
			cout << "Please enter a valid maze size." << endl;
		}
	}

	bool validExitPlayers = false;
	while (!validExitPlayers) {
		cout << "Please the starting amount of exits and players you would like. (15 exits max)" << endl;
		cin >> firstNumExitsPlayers;

		if (firstNumExitsPlayers > 0 && firstNumExitsPlayers <= 15) {
			validExitPlayers = true;
		}
		else {
			cout << "Please enter a valid number of exits/players." << endl;
		}
	}
	validExitPlayers = false;
	while (!validExitPlayers) {
		cout << "Please the amount of exits and players you would like. (more than the value enterred previously and <=15)" << endl;
		cin >> secondNumExitsPlayers;

		if (secondNumExitsPlayers > firstNumExitsPlayers && secondNumExitsPlayers <= 15) {
			validExitPlayers = true;
		}
		else {
			cout << "Please enter a valid number of exits/players." << endl;
		}
	}
	bool validOption = false;
	option = 0;
	bool printAllMazes = false;
	while (!validOption) {
		cout << "Would you like to print every maze generated. (THIS CAN TAKE A CONSIDERABLE AMOUNT OF TIME)" << endl;
		cout << "1.Yes" << endl;
		cout << "2.No" << endl;
		cin >> option;

		if (option ==1) {
			validOption = true;
			printAllMazes = true;
		}
		else if (option ==2) {
			validOption = true;
		}
		else {
			cout << "Please enter a valid number of exits/players." << endl;
		}
	}
	vector<MazeGenerator::MazeResults> results;
	for (int i = firstMapSize; i < lastMapSize; i++) {
		for (int j = firstNumExitsPlayers; j < secondNumExitsPlayers;j++) {
			MazeGenerator maze(i, j, j);
			results.push_back(maze.hundredMazeGeneration(printAllMazes));
			displayInformation(results,firstMapSize,lastMapSize,firstNumExitsPlayers,secondNumExitsPlayers);
		}
	}
}
