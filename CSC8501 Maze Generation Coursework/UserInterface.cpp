#include "MazeGenerator.h"
#include <iostream>
#include <time.h>
#include <string>
#include "UserInterface.h"
#include "Pathfinding.h"

using namespace std;

void UserInterface::printOptimalPaths() {
	bool optionSelected = false;
	while (!optionSelected) {
		int option;
		cout << endl;
		cout << "Would you like to print the optimal paths to the exits?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cin >> option;

		if (option ==1) {
			optionSelected = true;
			Pathfinding path(maze.map,maze.mapSize);
			for (int i = 0; i < maze.exits.size(); i++) {
				path.findShortestPath(maze.startingPosition, maze.exits.at(i));
			}
			maze.printMaze();
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
			maze.saveMaze(filename + ".txt");
			optionSelected = true;
		}
		else if(option==2){
			optionSelected = true;
		}
		else {
			cout << "Please enter a valid option." << endl;
			cout << '/n' << endl;
		}
	}
}


void UserInterface::generateRandomMaze() {
	int mapSize;
	int numExits;
	bool validSize = false;
	while (!validSize) {
		cout << "Please enter a map size, between 20 and 100 (e.g. map size of 20 will result in 20x20 map)" << endl;
		cin >> mapSize;

		if (mapSize <=100 && mapSize >=20) {
			validSize = true;
		}
		else {
			cout << "Please enter a valid maze size." << endl;
		}
	}
	bool validExits = false;
	while (!validExits) {
		cout << "Please the amount of exits you would like. (15 exits max)" << endl;
		cin >> numExits;

		if (numExits >0 && numExits <=15) {
			validExits = true;
		}
		else {
			cout << "Please enter a valid number of exits." << endl;
		}
	}
	maze = MazeGenerator(mapSize, numExits);
	maze.createMaze();
	maze.printMaze();
	printOptimalPaths();

	saveMaze();

}


void UserInterface::readMaze() {
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
			printOptimalPaths();
		}
	}
}