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

#endif