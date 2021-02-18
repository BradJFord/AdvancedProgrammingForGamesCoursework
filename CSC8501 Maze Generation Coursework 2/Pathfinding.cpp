#include "Pathfinding.h"

AStarNode* Pathfinding::initialiseNode(Positions pos, Positions destination, AStarNode* parentNode) {
	AStarNode* newNode = new AStarNode;
	newNode->pos.row = pos.row;
	newNode->pos.column = pos.column;
	newNode->parentNode = parentNode;
	newNode->h = distanceToDestination(pos, destination);
	newNode->g = parentNode->g + 1;
	newNode->f = newNode->g + newNode->h;
	return newNode;
}



int Pathfinding::distanceToDestination(Positions pos, Positions destination) {
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



vector<AStarNode*> Pathfinding::getAdjacentNodes(AStarNode* node, Positions destination) {
	vector<AStarNode*> adjacentNodes;

	Positions tempPos;
	tempPos.row = node->pos.row;
	tempPos.column = node->pos.column;

	if (tempPos.row > 0 && tempPos.row < mapSize - 1) {
		if ((*map)[tempPos.row + 1][tempPos.column] != 'x') {
			tempPos.row = tempPos.row + 1;
			adjacentNodes.push_back(initialiseNode(tempPos, destination, node));
		}

		tempPos.row = node->pos.row;
		tempPos.column = node->pos.column;

		if ((*map)[tempPos.row - 1][tempPos.column] != 'x') {
			tempPos.row = tempPos.row - 1;
			adjacentNodes.push_back(initialiseNode(tempPos, destination, node));
		}
	}

	tempPos.row = node->pos.row;
	tempPos.column = node->pos.column;

	if (tempPos.column > 0 && tempPos.column < mapSize - 1) {
		if ((*map)[tempPos.row][tempPos.column + 1] != 'x') {
			tempPos.column = tempPos.column + 1;
			adjacentNodes.push_back(initialiseNode(tempPos, destination, node));
		}

		tempPos.row = node->pos.row;
		tempPos.column = node->pos.column;

		if ((*map)[tempPos.row][tempPos.column - 1] != 'x') {
			tempPos.column = tempPos.column - 1;
			adjacentNodes.push_back(initialiseNode(tempPos, destination, node));
		}
	}
	return adjacentNodes;
}



AStarNode* Pathfinding::findSmallestFValue(vector<AStarNode*> evaluationList) {
	AStarNode* smallestFnode = evaluationList.at(0);
	for (int i = 1; i < evaluationList.size(); i++) {
		if (evaluationList.at(i)->f < smallestFnode->f) {
			smallestFnode = evaluationList.at(i);
		}
	}
	return smallestFnode;
}



bool Pathfinding::containsPosition(vector<AStarNode*> closedPath, Positions destination) {
	for (int i = 0; i < closedPath.size(); i++) {
		if ((closedPath.at(i)->pos.row == destination.row)) {
			if ((closedPath.at(i)->pos.column == destination.column)) {
				return true;
			}
		}
	}
	return false;
}


vector<AStarNode> Pathfinding::createFinalPath(AStarNode* destinationNode) {
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
	for (int i = flippedVector.size() - 1; i >= 0; i--) {
		finalVector.push_back(flippedVector.at(i));
	}

	return finalVector;

}

AStarNode* Pathfinding::initialiseStartingNode(Positions pos, Positions exit) {
	AStarNode* startingNode = new AStarNode;;
	startingNode->pos.row = pos.row;
	startingNode->pos.column = pos.column;
	startingNode->g = 0;
	startingNode->h = distanceToDestination(pos, exit);
	startingNode->f = startingNode->g + startingNode->h;
	startingNode->parentNode = nullptr;

	return startingNode;
}

void Pathfinding::eraseListPointers(vector<AStarNode*> evaluationList, vector<AStarNode*> closedPath) {
	for (int i = 0; i < evaluationList.size(); i++) {
		delete evaluationList.at(i);
	}
	for (int i = 0; i < closedPath.size(); i++) {
		delete closedPath.at(i);
	}
}
vector<AStarNode> Pathfinding::findShortestPath(Positions pos, Positions exit) {

	AStarNode* startingNode = initialiseStartingNode(pos, exit);
	vector<AStarNode*> evaluationList;
	vector<AStarNode*> closedPath;
	vector<AStarNode> finalPath;

	evaluationList.push_back(startingNode);
	AStarNode* currentNode;

	while (evaluationList.size() > 0) {
		currentNode = findSmallestFValue(evaluationList);
		closedPath.push_back(currentNode);
		int indexToRemove = 0;

		for (int i = 0; i < evaluationList.size(); i++) {
			if ((currentNode->pos.row == evaluationList.at(i)->pos.row) && (currentNode->pos.column == evaluationList.at(i)->pos.column)) {
				indexToRemove = i;
				break;
			}
		}
		evaluationList.erase(evaluationList.begin() + indexToRemove);

		if (containsPosition(closedPath, exit)) {
			finalPath = createFinalPath(currentNode);
			eraseListPointers(evaluationList, closedPath);
			evaluationList.clear();
			closedPath.clear();
			return finalPath;
			break;
		}

		vector<AStarNode*> adjacentNodes = getAdjacentNodes(currentNode, exit);
		for (int i = 0; i < adjacentNodes.size(); i++) {
			if (containsPosition(closedPath, adjacentNodes.at(i)->pos)) {
				continue;
			}
			if (!containsPosition(evaluationList, adjacentNodes.at(i)->pos)) {
				evaluationList.push_back(adjacentNodes.at(i));
			}
			else if ((adjacentNodes.at(i)->h) + (currentNode->g + 1) < adjacentNodes.at(i)->f) {
				adjacentNodes.at(i)->parentNode = currentNode;
			}
		}

	}
	return finalPath;
}