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
		for (int j = 0; j < (*map)[0].size(); j++) {
			(*map)[i][j] = ((*map)[i][j] == 'o') ? (*map)[i][j] = ' ' : (*map)[i][j];
			line.push_back((*map)[i][j]);
		}
		saveFile << line << endl;
	}
	saveFile.close();
}

void MazeGenerator::deletePlayers() {
	while (players.size() >0) {
		Player currentPlayer = players.at(0);
		(*map)[currentPlayer.pos.row][currentPlayer.pos.column] = ' ';
		players.erase(players.begin());

	}
}

Direction MazeGenerator::determineExitDirection(Positions pos) {
	if (pos.row == 0) {
		return UP;
	}
	else if (pos.row == mapSize - 1) {
		return DOWN;
	}
	else if (pos.column == 0) {
		return LEFT;
	}
	else if (pos.column == mapSize - 1) {
		return RIGHT;
	}
}

bool MazeGenerator::readMazeFile(string filename) {
	int exitCount = 0;
	int playerCounter = 0;
	ifstream inFile(filename);
	string line;
	if (inFile.is_open()) {
		int lineNumber = 0;
		while (getline(inFile, line)) {
			if (this->mapSize <= 0) {
				this->mapSize = line.size();
				map = new vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
			}
			for (int i = 0; i < line.size(); i++) {
				(*map)[lineNumber][i] = line[i];
				switch ((*map)[lineNumber][i]) {
					case 'E':
						exitCount++;
						Positions newExit;
						newExit.row = lineNumber;
						newExit.column = i;
						newExit.exitDirection = determineExitDirection(newExit);
						exits.push_back(newExit);
						break;
					case 'F':
						this->finishPosition.row = lineNumber;
						this->finishPosition.column = i;
						break;
					case 'P':
						Player newPlayer;
						newPlayer.pos.row = lineNumber;
						newPlayer.pos.column = i;
						players.push_back(newPlayer);
						playerCounter++;
						break;
				}

			}
			lineNumber++;
		}
		inFile.close();
		this->numPlayers = playerCounter;
		this->numExits = exitCount;
		return true;
	}
	else {
		{
			cout << "Unable to Open file" << endl;
			return false;
		}
	}
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

		if (checkPosition.row >= 1 && checkPosition.row < mapSize - 1) {
			if (checkPosition.column >= 1 && checkPosition.column < mapSize - 1) {
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
	for (int i = 0; i < (*map)[mapSize - 2].size(); i++) {
		if ((*map)[mapSize - 2][i] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == (*map)[mapSize - 2].size()) {
		for (int i = 0; i < (*map)[mapSize - 2].size(); i++) {
			if ((*map)[mapSize - 3][i] == 'x') {
				(*map)[mapSize - 2][i] = 'x';
			}
			else {
				(*map)[mapSize - 2][i] = ' ';
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
		if ((*map)[i][mapSize - 2] == 'x') {
			outerWallCount++;
		}
	}
	if (outerWallCount == map->size()) {
		for (int i = 0; i < map->size(); i++) {
			if ((*map)[i][mapSize - 3] == 'x') {
				(*map)[i][mapSize - 2] = 'x';
			}
			else {
				(*map)[i][mapSize - 2] = ' ';
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
	(*map)[finishPosition.row][finishPosition.column] = 'F';
}



void MazeGenerator::assignExits() {
	int failCount = 0;
	while (numExits > 0) {
		enum Direction direction = static_cast<Direction>(rand() % 4);

		int tempMazeSize = map->size() - 1;
		Positions potentialExit;
		switch (direction) {
			case UP:
				potentialExit.row = 0;
				potentialExit.column = rand() % tempMazeSize + 1;
				potentialExit.exitDirection = UP;
				break;
			case LEFT:
				potentialExit.row = rand() % map->size();
				potentialExit.column = 0;
				potentialExit.exitDirection = LEFT;
				break;
			case RIGHT:
				potentialExit.row = rand() % tempMazeSize + 1;
				potentialExit.column = tempMazeSize;
				potentialExit.exitDirection = RIGHT;
				break;
			case DOWN:
				potentialExit.row = tempMazeSize;
				potentialExit.column = rand() % tempMazeSize + 1;
				potentialExit.exitDirection = DOWN;
				break;
		}
		if (isValidExit(potentialExit, direction) && failCount < 50) {
			(*map)[potentialExit.row][potentialExit.column] = 'E';
			numExits--;

			Positions newExit;
			newExit.row = potentialExit.row;
			newExit.column = potentialExit.column;
			newExit.exitDirection = potentialExit.exitDirection;
			exits.push_back(newExit);
		}
		else {
			failCount++;
		}
	}
}

void MazeGenerator::createMaze(bool createPlayerList) {

	int halfSize = mapSize / 2;
	Positions startPos;
	startPos.row = rand() % halfSize + 1;
	startPos.column = rand() % halfSize + 1;

	finishPosition;
	finishPosition.row = (mapSize / 2) - 1;
	finishPosition.column = (mapSize / 2) - 1;

	createCorridors(startPos);
	removeOuterWalls();
	carveCentralRoom();
	assignExits();
	if (createPlayerList) {
		createPlayers();
	}
}

void MazeGenerator::createPlayers() {
	for (int i = 0; i < exits.size();i++) {
		Player newPlayer;

		switch (exits.at(i).exitDirection) {
			case UP:
				newPlayer.pos.row = exits.at(i).row + 1;
				newPlayer.pos.column = exits.at(i).column;
				break;
			case DOWN:
				newPlayer.pos.row = exits.at(i).row - 1;
				newPlayer.pos.column = exits.at(i).column;
				break;
			case LEFT:
				newPlayer.pos.row = exits.at(i).row;
				newPlayer.pos.column = exits.at(i).column + 1;
				break;
			case RIGHT:
				newPlayer.pos.row = exits.at(i).row;
				newPlayer.pos.column = exits.at(i).column - 1;
				break;
		}
		players.push_back(newPlayer);
	}
	for (int i = 0; i < players.size(); i++) {
		(*map)[players.at(i).pos.row][players.at(i).pos.column] = 'P';
	}
}


bool MazeGenerator::validMove(Player player) {
	if (player.path.size()>0) {
		Positions nextPlayerPos = player.path.at(0).pos;
		if ((*map)[nextPlayerPos.row][nextPlayerPos.column] != 'P' || (*map)[nextPlayerPos.row][nextPlayerPos.column] != 'x') {
			return true;
		}
	}
	return false;
}
bool MazeGenerator::finishingMove(Player player) {
	Positions nextPlayerPos = player.path.at(0).pos;
	if ((*map)[nextPlayerPos.row][nextPlayerPos.column] == 'F') {
		finishedPlayers++;
		return true;
	}
	return false;
}


void MazeGenerator::movePlayers(Pathfinding path) {
	for (int i = 0; i < players.size(); i++) {
		if (players.at(i).deadlocked == false && validMove(players.at(i))) {
			if (!finishingMove(players.at(i))) {
				players.at(i).stationaryTurns = 0;
				(*map)[players.at(i).pos.row][players.at(i).pos.column] = ' ';
				players.at(i).pos = players.at(i).path.at(0).pos;
				(*map)[players.at(i).pos.row][players.at(i).pos.column] = 'P';
				players.at(i).path.erase(players.at(i).path.begin());
			}
			else {
				playerFinishingTurn.push_back(turnCounter);
				(*map)[players.at(i).pos.row][players.at(i).pos.column] = ' ';
				players.erase(players.begin()+i);
			}
		}
		else {
			if (deadlockedPlayers>=players.size() && finishedPlayers <=0) {
				cout << endl;
				if (!hundredMazes) {
					cout << "Deadlock has occured. Program will end." << endl;
				}
				hundredMazeResults.deadlockCount++;
				players.clear();
			}else if (deadlockedPlayers >= players.size() && finishedPlayers >= 0) {
				cout << endl;
				if (!hundredMazes) {
					cout << "Maze is partially completeable." << endl;
				}
				hundredMazeResults.partialCompleteableCount++;
				players.clear();
			}
			if (players.size()>0) {
				players.at(i).stationaryTurns++;
				if (players.at(i).stationaryTurns >= 50) {
					deadlockedPlayers++;
					players.at(i).deadlocked = true;
				}
				else if (players.at(i).stationaryTurns >= 3) {
					players.at(i).path = path.findShortestPath(players.at(i).pos, finishPosition);
				}
			}
		}
	}

}


bool MazeGenerator::readPlayerProgress(string filename) {
	int exitCount = 0;
	ifstream inFile(filename);
	string line;
	if (inFile.is_open()) {
		int lineNumber = 0;
		while (getline(inFile, line)) {
			if (line[0] == '-') {
				playerProgressMap->push_back((*map));
				lineNumber = 0;
				getline(inFile,line);
			}
			if (this->mapSize <= 0) {
				this->mapSize = line.size();
				map = new vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
			}
			for (int i = 0; i < line.size(); i++) {
				(*map)[lineNumber][i] = line[i];
				if (playerProgressMap->size()<=0) {
					if ((*map)[lineNumber][i] == 'E') {
						exitCount++;

						Positions newExit;
						newExit.row = lineNumber;
						newExit.column = i;
						exits.push_back(newExit);
					}
					else if ((*map)[lineNumber][i] == 'F') {
						this->finishPosition.row = lineNumber;
						this->finishPosition.column = i;
					}
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


void MazeGenerator::savePlayerProgress(string filename) {
	ofstream saveFile;
	saveFile.open(filename);
	for (int i = 0; i < playerProgressMap->size(); i++) {
		for (int j = 0; j < playerProgressMap->at(i).size(); j++) {
			string line;
			for (int k = 0; k < playerProgressMap->at(i)[0].size(); k++) {
				playerProgressMap->at(i)[j][k] = (playerProgressMap->at(i)[j][k] == 'o') ? playerProgressMap->at(i)[j][k] = ' ' : playerProgressMap->at(i)[j][k];
				line.push_back(playerProgressMap->at(i)[j][k]);
			}
			saveFile << line << endl;
		}
		saveFile<< "---" << endl;
	}
	saveFile.close();
}


void MazeGenerator::printPlayerProgress() {
	vector<int> finishTurns = playerFinishingTurn;
	int finishedPlayerCount = 0;
	for (int i = 0; i < playerProgressMap->size();i++) {
		cout << '\n' << endl;
		cout << "Turn " << i+1 << endl;
		cout << '\n' << endl;
		for (int j = 0; j < playerProgressMap->at(i).size(); j++) {
			for (int k = 0; k < playerProgressMap->at(i)[0].size(); k++) {
				cout << playerProgressMap->at(i)[j][k] << "";
				if (k == (*map)[0].size() - 1) {
					cout << endl;
				}
			}
		}
		if (finishTurns.size()>0) {
			if (finishTurns[0] == i) {
				cout << endl;
				cout << "------------------------------------------------" << endl;
				cout << "Player " << finishedPlayerCount + 1 << " has reached the end will be despawned." << endl;
				cout << "------------------------------------------------" << endl;
				finishTurns.erase(finishTurns.begin());
				finishedPlayerCount++;
			}
		}
	}
}

void MazeGenerator::writeOptimalPathToMap(vector<AStarNode> path) {
	for (int i = 0; i < path.size(); i++) {
		int row = path.at(i).pos.row;
		int column = path.at(i).pos.column;
		if ((*map)[row][column] != 'E') {
			(*map)[row][column] = 'o';
		}
	}
}
void MazeGenerator::playerManager() {
	
	if (players.size()<=0) {
		createPlayers();
	}
	Pathfinding path(map,mapSize);
	for (int i = 0; i < players.size();i++) {
		players.at(i).path = path.findShortestPath(players.at(i).pos,finishPosition);
		playerProgressMap->push_back((*map));
	}
	while (players.size()>0) {
		movePlayers(path);
		turnCounter++;
		playerProgressMap->push_back((*map));
	}
	if (deadlockedPlayers <=0 && finishedPlayers >0) {
		if (!hundredMazes) {
			cout << "Maze is completeable" << endl;
		}
		hundredMazeResults.fullyCompleteableCount++;
	}
}

MazeGenerator::MazeResults MazeGenerator::hundredMazeGeneration(bool printAllMazes) {
	int numPlayersCopy = numPlayers;
	int numExitsCopy = numExits;
	hundredMazes = true;
	for (int i = 0; i < 100; i++) {

		exits.clear();
		map = new vector<vector<char>>(mapSize, vector<char>(mapSize, 'x'));
		playerProgressMap->clear();
		numPlayers = numPlayersCopy;
		numExits = numExitsCopy;
		createMaze(true);
		if (printAllMazes) {
			printMaze();
		}
		playerManager();
	}
	return hundredMazeResults;
}