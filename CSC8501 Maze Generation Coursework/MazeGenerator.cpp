#include "MazeGenerator.h"

MazeGenerator::AStarNode* MazeGenerator::initialiseNode(int row, int column, int destinationRow, int destinationColumn , AStarNode* parentNode) {
	AStarNode* newNode = new AStarNode;
	newNode->row = row;
	newNode->column = column;
	newNode->parentNode = parentNode;
	newNode->h = distanceToDestination(row, column, destinationRow, destinationColumn);
	newNode->g = parentNode->g + 1;
	newNode->f = newNode->g + newNode->h;
	return newNode;
}

int MazeGenerator::distanceToDestination(int currentRow, int currentColumn, int destinationRow, int destinationColumn) {
	int distanceCount = 0;
	int posOrNegativeRow = (currentRow <= destinationRow) ? 1 : -1;
	int posOrNegativeColumn = (currentColumn <= destinationColumn) ? 1 : -1;

	while (currentRow !=destinationRow) {
		currentRow = currentRow + posOrNegativeRow;
		distanceCount++;
	}
	while (currentColumn != destinationColumn) {
		currentColumn = currentColumn + posOrNegativeColumn;
		distanceCount++;
	}
	return distanceCount;
}
vector<MazeGenerator::AStarNode*> MazeGenerator::getAdjacentNodes(AStarNode* node, int destinatonRow, int destinationColumn) {
	vector<AStarNode*> adjacentNodes;

	int row = node->row;
	int column = node->column;
	if (row >0 && row < mapSize-1) {
		if (map[row + 1][column] != 'x') {
			adjacentNodes.push_back(initialiseNode(row + 1, column, destinatonRow, destinationColumn, node));
		}
		if (map[row - 1][column] != 'x') {
			adjacentNodes.push_back(initialiseNode(row - 1, column, destinatonRow, destinationColumn, node));
		}
	}
	if (column >0 && column < mapSize-1) {
		if (map[row][column + 1] != 'x') {
			adjacentNodes.push_back(initialiseNode(row, column + 1, destinatonRow, destinationColumn, node));
		}
		if (map[row][column - 1] != 'x') {
			adjacentNodes.push_back(initialiseNode(row, column - 1, destinatonRow, destinationColumn, node));
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
bool MazeGenerator::endReached(vector<AStarNode*> closedPath, int destinationRow, int destinationColumn) {
	for (int i = 0; i < closedPath.size(); i++) {

		//cout << closedPath.at(i).row << " " << closedPath.at(i).column << endl;
		if ((closedPath.at(i)->row == destinationRow)) {
			if ((closedPath.at(i)->column == destinationColumn)) {
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
		int row = finalVector.at(i).row;
		int column = finalVector.at(i).column;
		if (map[row][column] != 'E') {
			this->map[row][column] = 'o';
		}
	}
}
void MazeGenerator::findShortestPath(int row, int column, Positions exit) {
	
	int destinationRow = exit.row;
	int destinationColumn = exit.column;


	AStarNode* startingNode = new AStarNode;
	startingNode->row = row;
	startingNode->column = column;
	startingNode->g = 0;
	startingNode->h = distanceToDestination(row, column,destinationRow, destinationColumn);
	startingNode->f = startingNode->g + startingNode->h;
	startingNode->parentNode = nullptr;
	vector<AStarNode*> evaluationList;
	vector<AStarNode*> closedPath;
	evaluationList.push_back(startingNode);

	AStarNode* currentNode;

	while (evaluationList.size() > 0) {
		currentNode = findSmallestFValue(evaluationList);

		closedPath.push_back(currentNode);
		int indexToRemove = 0;
		for (int i = 0; i < evaluationList.size();i++) {
			if ((currentNode->row == evaluationList.at(i)->row) && (currentNode->column == evaluationList.at(i)->column)) {
				indexToRemove = i;
				break;
			}
		}
		evaluationList.erase(evaluationList.begin()+indexToRemove);

		if (endReached(closedPath, destinationRow, destinationColumn)) {
			createFinalPath(currentNode);
			break;
		}

		vector<AStarNode*> adjacentNodes = getAdjacentNodes(currentNode,destinationRow,destinationColumn);
		for (int i = 0; i < adjacentNodes.size();i++) {
			if (endReached(closedPath, adjacentNodes.at(i)->row,adjacentNodes.at(i)->column)) {
				continue;
			}
			if (!endReached(evaluationList,adjacentNodes.at(i)->row, adjacentNodes.at(i)->column)) {
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
			cout << map[i][j] << " ";
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
bool MazeGenerator::isValidExit(int row, int column, Direction dir) {
	if (dir == UP) {
		if (map[row+1][column] == ' ') {
			return true;
		}
	}
	else if (dir == DOWN) {
		if (map[row - 1][column] == ' ') {
			return true;
		}
	}
	else if (dir == LEFT) {
		if (map[row][column+1] == ' ') {
			return true;
		}
	}
	else if (dir == RIGHT) {
		if (map[row][column-1] == ' ') {
			return true;
		}
	}
	return false;
}
void MazeGenerator::createMaze() {
	
	int halfSize = mapSize / 2;
	int row = rand() % halfSize + 1;
	int column = rand() % halfSize + 1;

	startingPosition;
	startingPosition.row = (mapSize / 2) - 1;
	startingPosition.column = (mapSize / 2) - 1;

	createCorridors(row, column);
	
	//get rid of double wall if one exists
	
	removeOuterWalls();


	//carve the central starting room
	for (int i = -2; i < 1; i++) {
		for (int j = -2; j < 1; j++) {
			map[(mapSize / 2) + i][(mapSize / 2) + j] = ' ';
		}
	}

	map[startingPosition.row][startingPosition.column] = 'S';

	//assign exits
	int failCount = 0;
	while (numExits >0) {
		enum Direction direction = static_cast<Direction>(rand() % 4);

		int x;
		int y;
		int tempMazeSize = map.size() - 1;
		if (direction == Direction::UP) {
			x = 0;
			y = rand() % tempMazeSize + 1;
	
		}
		else if (direction == Direction::LEFT) {
			x = rand() % map.size();
			y = 0;


		}
		else if (direction == Direction::RIGHT) {
			y = tempMazeSize;
			x = rand() % tempMazeSize + 1;

		}
		else if (direction == Direction::DOWN) {
			y = rand() % tempMazeSize + 1;
			x = tempMazeSize;

		}
		if (isValidExit(x, y, direction) && failCount < 50) {
			map[x][y] = 'E';
			numExits--;

			Positions newExit;
			newExit.row = x;
			newExit.column = y;
			exits.push_back(newExit);
		}
		else {
			failCount++;
		}
	}

}