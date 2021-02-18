#pragma once
#include"Direction.h"
struct Positions {
	int row;
	int column;

	//only used to determine which side of the maze an exit/entrance is on.
	Direction exitDirection;
};