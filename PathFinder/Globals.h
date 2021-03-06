#pragma once

#ifndef INCLUDES_HEADERS
#define INCLUDES_HEADERS
#include <vector>
#include <queue>
#include <SFML/System.hpp>

struct Coordinate
{

	Coordinate(int x = 0, int y = 0)
	{
		X = x;
		Y = y;
	}

	int X;
	int Y;

	bool operator==(Coordinate a) const
	{
		if (a.X == X && a.Y == Y)
			return true;
		else
			return false;
	}

};

extern std::queue<std::vector<Coordinate>> WorkerQueue;

extern bool found_shortest_path;

extern sf::Mutex mutex;

extern int path_cycle_speed;

extern std::vector<Coordinate> final_path;

struct Branch
{
	Branch(Coordinate a = Coordinate())
	{
		Left = NULL;
		Right = NULL;
		Up = NULL;
		Down = NULL;

		Data = -1;
		Pos = a;
	}

	//Points to the left branch
	Branch* Left;

	//Points to the right branch
	Branch* Right;

	//Points down
	Branch* Down;

	//Points up
	Branch* Up;

	//Data defaults to negative 1
	int Data = -1;

	//Coordinate of the branch.
	Coordinate Pos;
};

#endif