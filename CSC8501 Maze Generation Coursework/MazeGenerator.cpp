#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "MazeGenerator.h"
#include <algorithm>


void MazeGenerator::printMaze() {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			cout << map[i][j] << " ";
			if (j == map[0].size() - 1) {
				cout << endl;
			}
		}
	}
}
bool MazeGenerator::checkNeighbourTiles(int row, int column, Direction dir) {
		if (dir == UP) {
			if (row>2) {
				if (map[row - 2][column] != ' ') {
					return true;
				}
			}
		}
		else if (dir == DOWN) {
			if (row<mapSize-2) {
				if (map[row + 2][column] != ' ') {
					return true;
				}
			}
		}
		else if (dir == LEFT) {
			if (column>2) {
				if (map[row][column - 2] != ' ') {
					return true;
				}
			}
		}
		else if (dir == RIGHT) {
			if (column < mapSize - 2) {
				if (map[row][column + 2] != ' ') {
					return true;
				}
			}
		}
		return false;
}
vector<int> MazeGenerator::getNewDirection() {
	vector<int> directions;
	for (int i = 0; i < 4; i++) {
		directions.push_back(i);
	}
	random_shuffle(directions.begin(), directions.end());
	return directions;
}

void MazeGenerator::createCorridors(int row, int column) {
	map[row][column] = ' ';
	vector<int> directions = getNewDirection();

	for (int i = 0; i < directions.size(); i++) {
		int newRow = 0;
		int newColumn = 0;
		direction = static_cast<Direction>(directions.at(i));
			
		if (direction == UP) {
			newRow = -1;
		}
		else if (direction == DOWN) {

			newRow = 1;
		}
		else if (direction == LEFT) {
		
			newColumn = -1;
		}
		else if (direction == RIGHT) {

			newColumn = 1;
		}
		int x2 = row + (newRow * 2);
		int y2 = column + (newColumn * 2);

		if (x2 >=  1 && x2 < mapSize-1) {
			if(y2 >= 1 && y2 < mapSize-1){
				if (map[x2][y2] == 'x') {
					map[x2 - newRow][y2 - newColumn] = ' ';
					createCorridors(x2, y2);
				}
			}
		}
	}	
			//printMaze();
			//cout << " " << endl;
			//cout << " " << endl;
}



void MazeGenerator::createMaze() {
	//carve the central 3x3 starting room
	for (int i = -2; i < 1; i++) {
		for (int j = -2; j < 1; j++) {
			map[(mapSize / 2) + i][(mapSize / 2) + j] = ' ';
		}
	}

	map[(mapSize / 2) - 1][(mapSize / 2) - 1] = 'S';

	//assign exits
	for (int i = 0; i < numExits;i++) {
		enum Direction direction = static_cast<Direction>(rand() % 4);
		
		int x;
		int y;
		
		if (direction == Direction::UP) {
			x = 0;
			y = rand() % map[0].size();
		}else if (direction == Direction::LEFT) {
			x = rand() % map.size();
			y = 0;
		}
		else if (direction == Direction::RIGHT) {
			x = map[0].size()-1;
			y = rand() % map.size();
		}
		else if (direction == Direction::DOWN) {
			x = rand() % map[0].size();
			y = map.size()-1;
		}
		map[x][y] = 'E';
	}

}
int main() {
	srand(time(NULL));
	int mapSize;
	int numExits;
	cout << "Please enter a map size, (e.g. map size of 20 will result in 20x20 map)" << endl;
	cin >> mapSize;
	cout << "Please the amount of exits you would like." << endl;
	cin >> numExits;
	MazeGenerator maze(mapSize,numExits);

	int row = rand() % mapSize/2;
	int column = rand() % mapSize/2;

	maze.createCorridors(row, column);

	maze.printMaze();


	return 0;
}