#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "MazeGenerator.h"


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

vector<int> MazeGenerator::createVerticalWall(int row, int point) {
	vector<int> path;
	cout << "Row: " << row << " Point: " << point << endl;
	map[row][point] = 'x';
	path.push_back(point);
	if (row <= 1) {
		cout << "down" << endl;
		for (int i = row; i < map[row].size() - 1; i++) {
			if (map[row + 1][point] == 'x') {
				map[row][point] = 'x';
				path.push_back(row);
				break;
			}
			else {
				map[row++][point] = 'x';
				path.push_back(row);
			}
		}

	}
	else if (row <= 18) {
		cout << "up" << endl;
		for (int i = row; i >=1 ; i--) {
			if (map[row - 1][point] == 'x') {
				map[row][point] = 'x';
				path.push_back(row);
				break;
			}
			else {
				map[row--][point] = 'x';
				path.push_back(row);
			}
		}
	}
	int pathSize = path.size() - 1;
	
	if (pathSize > 1) {
		path.erase(path.begin() + (rand() % pathSize));
		map[path.at(rand() % pathSize)][point] = ' ';
	}
	return path;
}
vector<int> MazeGenerator::createHorizontalWall(int row, int point) {
	vector<int> path;
	cout << "Row: " << row << " Point: " << point << endl;

	map[row][point] = 'x';
	path.push_back(point);
	if (point <= 1) {
		cout << "right" << endl;
		for (int i = point; i < map[row].size() - 1; i++) {
			if (map[row][point + 1] == 'x') {
				
				map[row][point] = 'x';
				path.push_back(point);
				break;
			}
			else {
				map[row][point++] = 'x';
				path.push_back(point);
			}
		}
	}
	else if (point <= 18) {
		cout << "left" << endl;
		for (int i = point; i >= 1; i--) {
			if (map[row][point - 1] == 'x') {
				
				map[row][point] = 'x';
				path.push_back(point);
				break;
			}
			else {
				map[row][point--] = 'x';
				path.push_back(point);
			}
		}
	}
	int pathSize = path.size() - 1;
	
	if (pathSize>1) {
		path.erase(path.begin() + (rand() % pathSize));
		map[row][path.at(rand() % pathSize)] = ' ';
	}
	return path;
}
void MazeGenerator::createCorridors(int bisectRow, int bisectPoint, int stop) {
	int row = bisectRow;
	int point = bisectPoint;

	//choose direction to bisect the map, based on the position of the bisection point
	cout << "Horizontal or Vert " <<horizontalOrVert << endl;
	vector<int> path;


	if (horizontalOrVert == 0) {
		path = createHorizontalWall(row, point);
		horizontalOrVert = 1;
	}
	else {
		path = createVerticalWall(row,point);
		horizontalOrVert = 0;
	}
	printMaze();
	


	cout << "path size: " << path.size() << endl;
	int randomRowPoint = path.size();
	randomRowPoint = rand() % randomRowPoint +1;
	//randomRowPoint = (randomRowPoint > 0) ? randomRowPoint : rand() % (mapSize - 2);
	stop--;

		if (horizontalOrVert == 0) {
			if (stop > 0) {
				createCorridors(randomRowPoint, bisectPoint, stop);
			}
		}
		else {
			if (stop > 0) {
				createCorridors(bisectRow, randomRowPoint, stop);
			}
		}
		//get random point on made line make a pathway, find another random point and pass it into the next recursive call

}


//rename to generate maze and call createCorridors at the start
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
	maze.horizontalOrVert = rand() % 2; //0 horizontal, 1 vertical

	//choose row and point to begin the bisection of the map
	int mapSize1 = maze.map.size() - 2;
	int bisectRow = (rand() % mapSize1) + 1;
	cout << " Row " << bisectRow << endl;
	int bisectPoint = ((rand() % 2) > 0) ? mapSize-2 : 1;
	//int bisectPoint = (rand() % mapSize1) + 1;
	cout << "Point " << bisectPoint << endl;


	//create outer wall of maze
	for (int i = 0; i < (mapSize - 1); i++) {
		maze.map[i][0] = 'x';
	}
	for (int i = 0; i < (mapSize - 1); i++) {
		maze.map[0][i] = 'x';
	}
	for (int i = 0; i < (mapSize - 1); i++) {
		maze.map[i][mapSize-1] = 'x';
	}
	for (int i = 0; i < (mapSize); i++) {
		maze.map[mapSize-1][i] = 'x';
	}
	maze.printMaze();

	maze.createCorridors(bisectRow, bisectPoint,30);
	//map = maze.createCorridors(map, bisectRow, bisectPoint);
	maze.printMaze();
	return 0;
}