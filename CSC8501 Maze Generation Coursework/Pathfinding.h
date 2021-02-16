#pragma once
#include <vector>
#include "AStarNode.h"
using namespace std;

class Pathfinding {
	public:
		Pathfinding(vector< vector<char>>* map, int mapSize) {
			this->map = map;
			this->mapSize = mapSize;
		}

		void findShortestPath(Positions pos, Positions exit);

	private:
		//returns nodes in every cardinal direction if they exist/are allowed to be used to create a path.
		vector<AStarNode*> getAdjacentNodes(AStarNode* node, Positions destination);
		int distanceToDestination(Positions currentPosition, Positions destination);
		AStarNode* initialiseNode(Positions pos, Positions destination, AStarNode* parentNode);
		AStarNode* findSmallestFValue(vector<AStarNode*> evaluationList);
		bool containsPosition(vector<AStarNode*> closedList, Positions destinaion);
		void createFinalPath(AStarNode* destinationNode);
		AStarNode* initialiseStartingNode(Positions pos, Positions exit);
		void eraseListPointers(vector<AStarNode*> evaluationList, vector<AStarNode*> closedPath);
		
		
		vector< vector<char>>* map;
		int mapSize;
};
