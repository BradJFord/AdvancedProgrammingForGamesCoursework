#include "MazeGenerator.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

void printOptimalPaths(MazeGenerator* maze) {
	bool optionSelected = false;
	while (!optionSelected) {
		int option;
		cout << endl;
		cout << "Would you like to print the optimal paths to the exits?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cin >> option;

		if (option == 1) {
			optionSelected = true;
			for (int i = 0; i < maze->exits.size(); i++) {
				maze->writeOptimalPathToMap(maze->findShortestPath(maze->finishPosition, maze->exits.at(i)));
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


void generateRandomMaze() {
	int mapSize;
	int numExitsPlayers;
	bool validSize = false;
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
	bool validExitPlayers = false;
	while (!validExitPlayers) {
		cout << "Please the amount of exits and players you would like. (15 exits max)" << endl;
		cin >> numExitsPlayers;

		if (numExitsPlayers > 0 && numExitsPlayers <= 15) {
			validExitPlayers = true;
		}
		else {
			cout << "Please enter a valid number of exits." << endl;
		}
	}
	MazeGenerator maze(mapSize, numExitsPlayers, numExitsPlayers);
	maze.createMaze();
	//maze.printMaze();
	maze.printPlayerProgress();
	maze.savePlayerProgress("testSave.txt");
	printOptimalPaths(&maze);

	saveMaze(maze);

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
			printOptimalPaths(&maze);
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
			cout << "3. Exit" << endl;

			cin >> option;

			if (option == 1) {
				optionSelected = true;
				generateRandomMaze();
			}
			else if (option == 2) {
				optionSelected = true;
				MazeGenerator maze;
				readMaze(maze);
			}
			else if (option == 3) {
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