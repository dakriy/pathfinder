#include<iostream>
#include<string>
#include<vector>

using namespace std;



int main()
{

	int Maze[10][10] = //Y //X
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