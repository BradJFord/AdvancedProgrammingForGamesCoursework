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

		if (option ==1) {
			optionSelected = true;
			for (int i = 0; i < maze->exits.size(); i++) {
				maze->findShortestPath(maze->startingPosition.row, maze->startingPosition.column, maze->exits.at(i));
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

void generateRandomMaze() {
	int mapSize;
	int numExits;
	cout << "Please enter a map size, (e.g. map size of 20 will result in 20x20 map)" << endl;
	cin >> mapSize;
	cout << "Please the amount of exits you would like." << endl;
	cin >> numExits;

	MazeGenerator maze(mapSize, numExits);
	maze.createMaze();
	maze.printMaze();

	printOptimalPaths(&maze);

}



int main() {
	srand(time(NULL));
	bool optionSelected = false;
	while (!optionSelected) {
		int option;
		cout << "1. Randomly Generate Maze" << endl;
		cout << "2. Read Maze From File" << endl;
		cin >> option;

		if (option == 1) {
			optionSelected = true;
			generateRandomMaze();
		}
		else if (option == 2) {
			MazeGenerator maze;
			maze.readMazeFile("mazeSave.txt");
			maze.printMaze();
			printOptimalPaths(&maze);
			optionSelected = true;
		}
		else {
			cout << "Please enter a valid option." << endl;
			cout <<'/n' << endl;
		}
	}

/*

	option = 0;
	cout << "1. Save Maze To File" << endl;

	cin >> option;

	if (option == 1) {
		maze.saveMaze();
	}
	*/
	return 0;
}