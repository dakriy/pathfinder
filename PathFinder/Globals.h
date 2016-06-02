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

	Branch(Coordinate a = Coordinate())
	{
		Left = NULL;
		Right = NULL;
		Data = -1;
		Pos = a;
	}

	//Points to the left branch
	Branch* Left;


	//Points to the right branch
	Branch* Right;

	//Data defaults to negative 1
	int Data;

	//Coordinate of the branch.
	Coordinate Pos;
};

#endif