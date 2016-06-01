#pragma once

#ifndef INCLUDES_HEADERS
#define INCLUDES_HEADERS

struct Coordinate
{

	Coordinate(int x = 0, int y = 0)
	{
		X = x;
		Y = y;
	}

	int X;
	int Y;
};

struct Branch
{
	//Points to the left branch
	Branch* Left = NULL;

	//Points to the right branch
	Branch* Right = NULL;

	//Data defaults to negative 1
	int Data = -1;

	//Coordinate of the branch.
	Coordinate Pos = Coordinate();
};

#endif