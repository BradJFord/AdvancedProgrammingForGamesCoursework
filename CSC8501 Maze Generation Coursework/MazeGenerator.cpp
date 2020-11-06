#include "MazeGenerator.h"

MazeGenerator::AStarNode* MazeGenerator::initialiseNode(Positions pos, Positions destination , AStarNode* parentNode) {
	AStarNode* newNode = new AStarNode;
	newNode->pos.row = pos.row;
	newNode->pos.column = pos.column;
	newNode->parentNode = parentNode;
	newNode->h = distanceToDestination(pos, destination);
	newNode->g = parentNode->g + 1;
	newNode->f = newNode->g + newNode->h;
	return newNode;
}



int MazeGenerator::distanceToDestination(Positions pos, Positions destination) {
	int distanceCount = 0;
	int posOrNegativeRow = (pos.row <= destination.row) ? 1 : -1;
	int posOrNegativeColumn = (pos.column <= destination.column) ? 1 : -1;

	while (pos.row != destination.row) {
		pos.row = pos.row + posOrNegativeRow;
		distanceCount++;
	}
	while (pos.column != destination.column) {
		pos.column = pos.column + posOrNegativeColumn;
		distanceCount++;
	}
	return distanceCount;
}



vector<MazeGenerator::AStarNode*> MazeGenerator::getAdjacentNodes(AStarNode* node, Positions destination) {
	vector<AStarNode*> adjacentNodes;

	Positions tempPos;
	tempPos.row = node->pos.row;
	tempPos.column = node->pos.column;

	if (tempPos.row >0 && tempPos.row < mapSize-1) {
		if (map[tempPos.row + 1][tempPos.column] != 'x') {
			tempPos.row = tempPos.row + 1;
			adjacentNodes.push_back(initialiseNode(tempPos, destination, node));
		}

		tempPos.row = node->pos.row;
		tempPos.column = node->pos.column;

		if (map[tempPos.row - 1][tempPos.column] != 'x') {
			tempPos.row = tempPos.row - 1;
			adjacentNodes.push_back(initialiseNode(tempPos, destination, node));
		}
	}

	tempPos.row = node->pos.row;
	tempPos.column = node->pos.column;

	if (tempPos.column >0 && tempPos.column < mapSize-1) {
		if (map[tempPos.row][tempPos.column + 1] != 'x') {
			tempPos.column = tempPos.column + 1;
			adjacentNodes.push_back(initialiseNode(tempPos, destination, node));
		}

		tempPos.row = node->pos.row;
		tempPos.column = node->pos.column;

		if (map[tempPos.row][tempPos.column - 1] != 'x') {
			tempPos.column = tempPos.column - 1;
			adjacentNodes.push_back(initialiseNode(tempPos, destination, node));
		}
	}
	return adjacentNodes;
}



MazeGenerator::AStarNode* MazeGenerator::findSmallestFValue(vector<AStarNode*> evaluationList) {
	AStarNode* smallestFnode = evaluationList.at(0);
	for (int i = 1; i < evaluationList.size();i++) {
		if (evaluationList.at(i)->f < smallestFnode->f) {
			smallestFnode = evaluationList.at(i);
		}
	}
	return smallestFnode;
}



bool MazeGenerator::containsPosition(vector<AStarNode*> closedPath, Positions destination) {
	for (int i = 0; i < closedPath.size(); i++) {
		if ((closedPath.at(i)->pos.row == destination.row)) {
			if ((closedPath.at(i)->pos.column == destination.column)) {
				return true;
			}
		}
	}
	return false;
}



void MazeGenerator::createFinalPath(AStarNode* destinationNode) {
	vector<AStarNode> flippedVector;
	AStarNode* currentNode = destinationNode;
	flippedVector.push_back(*currentNode);
	while (currentNode->parentNode != nullptr) {
		currentNode = currentNode->parentNode;
		if (currentNode->parentNode != nullptr) {
			flippedVector.push_back(*currentNode);
		}
	}
	vector<AStarNode> finalVector;
	for (int i = flippedVector.size()-1; i >=0;i--) {
		finalVector.push_back(flippedVector.at(i));
	}
	for (int i = 0; i < finalVector.size(); i++) {
		int row = finalVector.at(i).pos.row;
		int column = finalVector.at(i).pos.column;
		if (map[row][column] != 'E') {
			this->map[row][column] = 'o';
		}
	}
}

MazeGenerator::AStarNode* MazeGenerator::initialiseStartingNode(Positions pos, Positions exit) {
	AStarNode* startingNode = new AStarNode;;
	startingNode->pos.row = pos.row;
	startingNode->pos.column = pos.column;
	startingNode->g = 0;
	startingNode->h = distanceToDestination(pos, exit);
	startingNode->f = startingNode->g + startingNode->h;
	startingNode->parentNode = nullptr;

	return startingNode;
}

void MazeGenerator::eraseListPointers(vector<AStarNode*> evaluationList, vector<AStarNode*> closedPath) {
	for (int i = 0; i < evaluationList.size(); i++) {
		delete evaluationList.at(i);
	}
	for (int i = 0; i < closedPath.size(); i++) {
		delete closedPath.at(i);
	}
}
void MazeGenerator::findShortestPath(Positions pos, Positions exit) {
	
	AStarNode* startingNode = initialiseStartingNode(pos, exit);
	vector<AStarNode*> evaluationList;
	vector<AStarNode*> closedPath;

	evaluationList.push_back(startingNode);
	AStarNode* currentNode;

	while (evaluationList.size() > 0) {
		currentNode = findSmallestFValue(evaluationList);
		closedPath.push_back(currentNode);
		int indexToRemove = 0;

		for (int i = 0; i < evaluationList.size();i++) {
			if ((currentNode->pos.row == evaluationList.at(i)->pos.row) && (currentNode->pos.column == evaluationList.at(i)->pos.column)) {
				indexToRemove = i;
				break;
			}
		}
		evaluationList.erase(evaluationList.begin()+indexToRemove);

		if (containsPosition(closedPath, exit)) {
			createFinalPath(currentNode);
			eraseListPointers(evaluationList, closedPath);
			evaluationList.clear();
			closedPath.clear();
			break;
		}

		vector<AStarNode*> adjacentNodes = getAdjacentNodes(currentNode,exit);
		for (int i = 0; i < adjacentNodes.size();i++) {
			if (containsPosition(closedPath, adjacentNodes.at(i)->pos)) {
				continue;
			}
			if (!containsPosition(evaluationList,adjacentNodes.at(i)->pos)) {
				evaluationList.push_back(adjacentNodes.at(i));
			}
			else if ((adjacentNodes.at(i)->h) + (currentNode->g +1) < adjacentNodes.at(i)->f) {
				adjacentNodes.at(i)->parentNode = currentNode;
			}
		}
	
	}

}



void MazeGenerator::printMaze() {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			cout << map[i][j] << "";
			if (j == map[0].size() - 1) {
				cout << endl;
			}
		}
	}
}



void MazeGenerator::saveMaze(string filename) {
	ofstream saveFile;
	saveFile.open(filename);
	for (int i = 0; i < map.size(); i++) {
		string line;
		for (int j = 0; j < map[0].size();j++) {
			map[i][j] = (map[i][j] == 'o') ? map[i][j] = ' ' : map[i][j];
			line.push_back(map[i][j]);
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
				map = vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
			}
			for (int i = 0; i < line.size(); i++) {
				map[lineNumber][i] = line[i];
				if (map[lineNumber][i] == 'E') {
					exitCount++;

					Positions newExit;
					newExit.row = lineNumber;
					newExit.column = i;
					exits.push_back(newExit);
				}
				else if (map[lineNumber][i] == 'S') {
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
		if (dir == UP) {
			if (pos.row>2) {
				if (map[pos.row - 2][pos.column] != ' ') {
					return true;
				}
			}
		}
		else if (dir == DOWN) {
			if (pos.row<mapSize-2) {
				if (map[pos.row + 2][pos.column] != ' ') {
					return true;
				}
			}
		}
		else if (dir == LEFT) {
			if (pos.column>2) {
				if (map[pos.row][pos.column - 2] != ' ') {
					return true;
				}
			}
		}
		else if (dir == RIGHT) {
			if (pos.column < mapSize - 2) {
				if (map[pos.row][pos.column + 2] != ' ') {
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


void MazeGenerator::createCorridors(Positions pos) {
	map[pos.row][pos.column] = ' ';
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
				if (map[checkPosition.row][checkPosition.column] == 'x') {
					map[checkPosition.row - newRow][checkPosition.column - newColumn] = ' ';
					createCorridors(checkPosition);
				}
			}
		}
	}
}


void MazeGenerator::removeOuterWalls() {
	int outerWallCount = 0;
	//top wall
	for (int i = 0; i < map[1].size(); i++) {
		if (map[1][i] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == map[1].size()) {
		for (int i = 0; i < map[1].size(); i++) {
			if (map[2][i] == 'x') {
				map[1][i] = 'x';
			}
			else {
				map[1][i] = ' ';
			}
		}
	}
	//bottom wall
	outerWallCount = 0;
	for (int i = 0; i < map[mapSize-2].size(); i++) {
		if (map[mapSize-2][i] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == map[mapSize-2].size()) {
		for (int i = 0; i < map[mapSize-2].size(); i++) {
			if (map[mapSize-3][i] == 'x') {
				map[mapSize-2][i] = 'x';
			}
			else {
				map[mapSize-2][i] = ' ';
			}
		}
	}
	//left wall
	outerWallCount = 0;
	for (int i = 0; i < map.size(); i++) {
		if (map[i][1] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == map.size()) {
		for (int i = 0; i < map.size(); i++) {
			if (map[i][2] == 'x') {
				map[i][1] = 'x';
			}
			else {
				map[i][1] = ' ';
			}
		}
	}
	//right wall
	outerWallCount = 0;
	for (int i = 0; i < map.size(); i++) {
		if (map[i][mapSize-2] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == map.size()) {
		for (int i = 0; i < map.size(); i++) {
			if (map[i][mapSize-3] == 'x') {
				map[i][mapSize-2] = 'x';
			}
			else {
				map[i][mapSize-2] = ' ';
			}
		}
	}
}



bool MazeGenerator::isValidExit(Positions pos, Direction dir) {
	if (dir == UP) {
		if (map[pos.row+1][pos.column] == ' ') {
			return true;
		}
	}
	else if (dir == DOWN) {
		if (map[pos.row - 1][pos.column] == ' ') {
			return true;
		}
	}
	else if (dir == LEFT) {
		if (map[pos.row][pos.column+1] == ' ') {
			return true;
		}
	}
	else if (dir == RIGHT) {
		if (map[pos.row][pos.column-1] == ' ') {
			return true;
		}
	}
	return false;
}



void MazeGenerator::carveCentralRoom() {
	for (int i = -2; i < 1; i++) {
		for (int j = -2; j < 1; j++) {
			map[(mapSize / 2) + i][(mapSize / 2) + j] = ' ';
		}
	}
	map[startingPosition.row][startingPosition.column] = 'S';
}



void MazeGenerator::assignExits() {
	int failCount = 0;
	while (numExits > 0) {
		enum Direction direction = static_cast<Direction>(rand() % 4);

		int tempMazeSize = map.size() - 1;
		Positions potentialExit;
		if (direction == Direction::UP) {
			potentialExit.row = 0;
			potentialExit.column = rand() % tempMazeSize + 1;

		}
		else if (direction == Direction::LEFT) {
			potentialExit.row = rand() % map.size();
			potentialExit.column = 0;


		}
		else if (direction == Direction::RIGHT) {
			potentialExit.row = rand() % tempMazeSize + 1;
			potentialExit.column = tempMazeSize;

		}
		else if (direction == Direction::DOWN) {
			potentialExit.row = tempMazeSize;
			potentialExit.column = rand() % tempMazeSize + 1;

		}
		if (isValidExit(potentialExit, direction) && failCount < 50) {
			map[potentialExit.row][potentialExit.column] = 'E';
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