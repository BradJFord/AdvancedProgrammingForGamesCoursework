#pragma once
#include <vector>
#include "AStarNode.h"

using namespace std;
class Pathfinding
{
	public:
		Pathfinding(vector< vector<char>>* map, int mapSize) {
			this->map = map;
			this->mapSize = mapSize;
		}

		vector<AStarNode> findShortestPath(Positions pos, Positions exit);

	private:

		AStarNode* initialiseNode(Positions pos, Positions destination, AStarNode* parentNode);
		int distanceToDestination(Positions pos, Positions destination);
		vector<AStarNode*> getAdjacentNodes(AStarNode* node, Positions destination);
		AStarNode* findSmallestFValue(vector<AStarNode*> evaluationList);
		bool containsPosition(vector<AStarNode*> closedPath, Positions destination);
		vector<AStarNode> createFinalPath(AStarNode* destinationNode);
		AStarNode* initialiseStartingNode(Positions pos, Positions exit);
		void eraseListPointers(vector<AStarNode*> evaluationList, vector<AStarNode*> closedPath);


		vector< vector<char>>* map;
		int mapSize;
};

