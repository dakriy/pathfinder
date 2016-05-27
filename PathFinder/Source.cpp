#include<iostream>
#include<string>
#include<vector>
#include"Globals.h"

using namespace std;



int main()
{

	vector<vector<int>>  Maze = //Y //X
	{
		{ 1,0,0,1,1 },
		{ 1,1,1,0,1 },
		{ 0,0,1,0,1 },
		{ 0,1,1,1,1 },
		{ 0,0,1,0,0 },
		{ 1,1,1,1,1 },
		{ 0,0,1,0,0 },
		{ 1,1,1,1,0 },
		{ 0,1,0,1,0 },
		{ 0,1,0,1,1 }
	};

	Coordinate BeginMaze = Coordinate(0,0);
	Coordinate EndMaze = Coordinate(10,10);

}