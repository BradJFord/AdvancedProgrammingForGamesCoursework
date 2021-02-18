#pragma once
#include "positions.h"
struct AStarNode {
	int g; //number of steps from point starting position to current position.
	int h; // number of steps from current position to destination.
	AStarNode* parentNode; //stores previous node.


	//current position (row is x and y is column)
	Positions pos;

	int f; //sum of g and h
};