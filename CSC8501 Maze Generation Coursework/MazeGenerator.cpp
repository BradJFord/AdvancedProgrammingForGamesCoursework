#include "MazeGenerator.h"

void MazeGenerator::printMaze() {
	for (int i = 0; i < map->size(); i++) {
		for (int j = 0; j < (*map)[0].size(); j++) {
			cout << (*map)[i][j] << "";
			if (j == (*map)[0].size() - 1) {
				cout << endl;
			}
		}
	}
}



void MazeGenerator::saveMaze(string filename) {
	ofstream saveFile;
	saveFile.open(filename);
	for (int i = 0; i < map->size(); i++) {
		string line;
		for (int j = 0; j < (*map)[0].size();j++) {
			(*map)[i][j] = ((*map)[i][j] == 'o') ? (*map)[i][j] = ' ' : (*map)[i][j];
			line.push_back((*map)[i][j]);
		}
		saveFile << line << endl;
	}
	saveFile.close();
}



bool MazeGenerator::readMazeFile(string filename) {
	int exitCount = 0;
	ifstream inFile(filename);
	string line;
	if (inFile.is_open()) {
		int lineNumber = 0;
		while (getline(inFile,line)) {
			if (this->mapSize<=0) {
				this->mapSize = line.size();
				map = new vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
			}
			for (int i = 0; i < line.size(); i++) {
				(*map)[lineNumber][i] = line[i];
				if ((*map)[lineNumber][i] == 'E') {
					exitCount++;

					Positions newExit;
					newExit.row = lineNumber;
					newExit.column = i;
					exits.push_back(newExit);
				}
				else if ((*map)[lineNumber][i] == 'S') {
					this->startingPosition.row = lineNumber;
					this->startingPosition.column = i;
				}
			}
			lineNumber++;
		}
		inFile.close();
		return true;
	}
	else {
		{
			cout << "Unable to Open file" << endl;
			return false;
		}
	}
	this->numExits = exitCount;
}



bool MazeGenerator::checkNeighbourTiles(Positions pos, Direction dir) {
	switch (dir) {
		case UP:
			if (pos.row > 2) {
				if ((*map)[pos.row - 2][pos.column] != ' ') {
					return true;
				}
			}
			break;
		case DOWN:
			if (pos.row < mapSize - 2) {
				if ((*map)[pos.row + 2][pos.column] != ' ') {
					return true;
				}
			}
			break;
		case LEFT:
			if (pos.column > 2) {
				if ((*map)[pos.row][pos.column - 2] != ' ') {
					return true;
				}
			}
			break;
		case RIGHT:
			if (pos.column < mapSize - 2) {
				if ((*map)[pos.row][pos.column + 2] != ' ') {
					return true;
				}
			}
			break;
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


void MazeGenerator::createCorridors(Positions pos) {
	(*map)[pos.row][pos.column] = ' ';
	vector<int> directions = getNewDirection();

	for (int i = 0; i < directions.size(); i++) {
		int newRow = 0;
		int newColumn = 0;
		direction = static_cast<Direction>(directions.at(i));
			
		newRow = (direction == UP) ? -1 : newRow;
		newRow = (direction == DOWN) ? 1 : newRow;
		newColumn = (direction == LEFT) ? -1 : newColumn;
		newColumn = (direction == RIGHT) ? 1 : newColumn;

		Positions checkPosition;
		checkPosition.row = pos.row + (newRow * 2);
		checkPosition.column = pos.column + (newColumn * 2);

		if (checkPosition.row >=  1 && checkPosition.row < mapSize-1) {
			if(checkPosition.column >= 1 && checkPosition.column < mapSize-1){
				if ((*map)[checkPosition.row][checkPosition.column] == 'x') {
					(*map)[checkPosition.row - newRow][checkPosition.column - newColumn] = ' ';
					createCorridors(checkPosition);
				}
			}
		}
	}
}


void MazeGenerator::removeOuterWalls() {
	int outerWallCount = 0;
	//top wall
	for (int i = 0; i < (*map)[1].size(); i++) {
		if ((*map)[1][i] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == (*map)[1].size()) {
		for (int i = 0; i < (*map)[1].size(); i++) {
			if ((*map)[2][i] == 'x') {
			(*map)[1][i] = 'x';
			}
			else {
				(*map)[1][i] = ' ';
			}
		}
	}
	//bottom wall
	outerWallCount = 0;
	for (int i = 0; i < (*map)[mapSize-2].size(); i++) {
		if ((*map)[mapSize-2][i] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == (*map)[mapSize-2].size()) {
		for (int i = 0; i < (*map)[mapSize-2].size(); i++) {
			if ((*map)[mapSize-3][i] == 'x') {
				(*map)[mapSize-2][i] = 'x';
			}
			else {
				(*map)[mapSize-2][i] = ' ';
			}
		}
	}
	//left wall
	outerWallCount = 0;
	for (int i = 0; i < map->size(); i++) {
		if ((*map)[i][1] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == map->size()) {
		for (int i = 0; i < map->size(); i++) {
			if ((*map)[i][2] == 'x') {
				(*map)[i][1] = 'x';
			}
			else {
				(*map)[i][1] = ' ';
			}
		}
	}
	//right wall
	outerWallCount = 0;
	for (int i = 0; i < map->size(); i++) {
		if ((*map)[i][mapSize-2] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == map->size()) {
		for (int i = 0; i < map->size(); i++) {
			if ((*map)[i][mapSize-3] == 'x') {
				(*map)[i][mapSize-2] = 'x';
			}
			else {
				(*map)[i][mapSize-2] = ' ';
			}
		}
	}
}



bool MazeGenerator::isValidExit(Positions pos, Direction dir) {
	switch (dir) {
		case UP:
			if ((*map)[pos.row + 1][pos.column] == ' ') {
				return true;
			}
			break;
		case DOWN:
			if ((*map)[pos.row - 1][pos.column] == ' ') {
				return true;
			}
			break;
		case LEFT:
			if ((*map)[pos.row][pos.column + 1] == ' ') {
				return true;
			}
			break;
		case RIGHT:
			if ((*map)[pos.row][pos.column - 1] == ' ') {
				return true;
			}
			break;
	}
	return false;
}



void MazeGenerator::carveCentralRoom() {
	for (int i = -2; i < 1; i++) {
		for (int j = -2; j < 1; j++) {
			(*map)[(mapSize / 2) + i][(mapSize / 2) + j] = ' ';
		}
	}
	(*map)[startingPosition.row][startingPosition.column] = 'S';
}



void MazeGenerator::assignExits() {
	int failCount = 0;
	while (numExits > 0) {
		enum Direction direction = static_cast<Direction>(rand() % 4);

		int tempMazeSize = map->size() - 1;
		Positions potentialExit;

		switch (direction) {
			case Direction::UP:
				potentialExit.row = 0;
				potentialExit.column = rand() % tempMazeSize + 1;
				break;
			case Direction::LEFT:
				potentialExit.row = rand() % map->size();
				potentialExit.column = 0;
				break;
			case Direction::RIGHT:
				potentialExit.row = rand() % tempMazeSize + 1;
				potentialExit.column = tempMazeSize;
				break;
			case Direction::DOWN:
				potentialExit.row = tempMazeSize;
				potentialExit.column = rand() % tempMazeSize + 1;
		}

		if (isValidExit(potentialExit, direction) && failCount < 50) {
			(*map)[potentialExit.row][potentialExit.column] = 'E';
			numExits--;

			Positions newExit;
			newExit.row = potentialExit.row;
			newExit.column = potentialExit.column;
			exits.push_back(newExit);
		}
		else {
			failCount++;
		}
	}
}

void MazeGenerator::createMaze() {
	
	int halfSize = mapSize / 2;
	Positions startPos;
	startPos.row = rand() % halfSize + 1;
	startPos.column = rand() % halfSize + 1;

	startingPosition;
	startingPosition.row = (mapSize / 2) - 1;
	startingPosition.column = (mapSize / 2) - 1;

	createCorridors(startPos);	
	removeOuterWalls();
	carveCentralRoom();
	assignExits();
}