#include "MazeGenerator.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

bool printOptimalPaths(MazeGenerator* maze, bool playerFlag) {
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
				for (int i = 0; i < maze->players.size(); i++) {
					maze->writeOptimalPathToMap(maze->findShortestPath(maze->players.at(i).pos, maze->finishPosition));
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
			for (int i = 0; i < maze->exits.size(); i++) {
				maze->writeOptimalPathToMap(maze->findShortestPath(maze->exits.at(i), maze->finishPosition));
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


void saveMaze(MazeGenerator maze) {
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
			maze.saveMaze(filename + ".txt");
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


bool generatePlayersOrNot() {
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

MazeGenerator generateRandomMaze() {
	int mapSize;
	int numExitsPlayers;
	int option;
	int numExits;
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

	//yes players
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

	//no players
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
	MazeGenerator maze(mapSize, numExits, numExitsPlayers);
	maze.createMaze(playerFlag);
	maze.printMaze();
	if (!printOptimalPaths(&maze, playerFlag)){
		saveMaze(maze);
	}

	return maze;
}


void readMaze(MazeGenerator maze) {
	bool validFile = false;
	while (!validFile) {
		cout << "Please enter the file you would like to read (without '.txt')" << endl;
		cout << "" << endl;
		string filename;
		cin >> filename;
		if (!maze.readMazeFile(filename + ".txt")) {
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
			maze.printMaze();


			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			printOptimalPaths(&maze, false);
		}
	}
}
void readPlayerProgressFile() {
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
bool playGame(MazeGenerator maze) {
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

void saveProgress(MazeGenerator maze) {
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
			cout << "Please enter the name of the file you would like to save. (without '.txt')";
			cin >> filename;
			maze.savePlayerProgress("beans.txt");
		}
		else if (option == 2) {
			validOption = true;
		}
		else {
			cout << "Please enter a valid option" << endl;
		}
	}
}
void printProgress(MazeGenerator maze) {
	int option;
	bool validOption = false;
	while (!validOption) {
		cout << "Would you like to print player progress?" << endl;
		cout << "1.Yes" << endl;
		cout << "2.No" << endl;
		cin >> option;

		if (option == 1) {
			validOption = true;
			maze.printPlayerProgress();
			saveProgress(maze);
		}
		else if (option == 2) {
			validOption = true;
		}
		else {
			cout << "Please enter a valid option" << endl;
		}
	}
	
}

int main() {
	srand(time(NULL));
	bool endFlag = false;
	while (!endFlag) {
		bool optionSelected = false;
		while (!optionSelected) {
			int option;
			cout << "1. Randomly Generate Maze" << endl;
			cout << "2. Read Maze From File" << endl;
			cout << "3. Read And Print Player Progress From File" << endl;
			cout << "4. Exit" << endl;

			cin >> option;

			if (option == 1) {
				optionSelected = true;
				MazeGenerator maze = generateRandomMaze();
				
				if (playGame(maze)) {
					maze.playerManager();
					printProgress(maze);
				}
			}
			else if (option == 2) {
				optionSelected = true;
				MazeGenerator maze;
				readMaze(maze);
			}
			else if (option == 3) {
				optionSelected = true;
				readPlayerProgressFile();

			}
			else if (option == 4) {
				endFlag = true;
				optionSelected = true;
			}
			else {
				cout << "Please enter a valid option." << endl;
				cout << '/n' << endl;
			}

		}
	}
	return 0;
}