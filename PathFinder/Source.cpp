#include<iostream>
#include<string>
#include<vector>
#include"Globals.h"
#include "PathFinder.h"

using namespace std;



int main()
{

	vector<vector<int>>  Maze = //Y //X
	{
		{ 1,1,1,1,1,1,1},
		{ 0,1,0,1,0,0,0 },
		{ 0,1,0,1,1,1,0 },
		{ 0,1,1,1,0,1,1 },
		{ 0,0,1,0,0,0,1 },
		{ 0,1,1,1,1,1,1 },
		{ 0,1,0,1,0,0,0 },
		{ 0,1,1,1,1,1,1 },
		{ 0,1,0,1,0,0,0 },
		{ 0,1,0,1,1,1,0 },
		{ 0,1,1,1,0,1,1 },
		{ 0,0,1,0,0,0,1 },
		{ 0,1,1,1,1,1,1 },
		{ 0,1,0,1,0,0,0 },
		{ 0,1,1,1,1,1,1 },
		{ 0,1,0,1,0,0,0 },
		{ 0,1,0,1,1,1,0 },
		{ 0,1,1,1,0,1,1 },
		{ 0,0,1,0,0,0,1 },
		{ 0,1,1,1,1,1,1 },
		{ 0,1,0,1,0,0,0 },
		{ 0,1,1,1,1,1,1 }
	};

	Coordinate BeginMaze = Coordinate(0,0);
	Coordinate EndMaze = Coordinate(6,21);

	PathFinder A = PathFinder(Maze, BeginMaze, EndMaze);

	
	Branch Root(BeginMaze);

	Branch *RealRoot = &Root;

	vector<Coordinate> Path;
	Path.push_back(BeginMaze);

	A.BranchAll(BeginMaze, Path, RealRoot);

	Path = A.GetShortest(EndMaze);

	cout << "Path Size:" << endl;
	cout << Path.size() << endl;

	cout << endl;
	cout << "Displaying Path!" << endl;

	//Display Path!
	for (int i = 0; i < Path.size(); i++)
	{
		cout << "X: " << Path[i].X << "Y: " << Path[i].Y << " || ";
	}

	vector<vector<int>> DMaze = Maze;

	for (int y = 0; y < DMaze.size(); y++)
	{
		for (int x = 0; x < DMaze[0].size(); x++)
		{
			for (int i = 0; i < Path.size(); i++)
			{
				if (Path[i].X == x && Path[i].Y == y)
				{
					DMaze[y][x] = 3;
				}
			}
		}
	}

	for (int y = 0; y < Maze.size(); y++)
	{
		cout << endl;
		for (int x = 0; x < Maze[0].size(); x++)
		{
			cout << " " << DMaze[y][x];
		}
	}

	A.NavDeepDelete(RealRoot);

	//Pauses Program
	system("PAUSE");

	//Ends Program
	return 0;
}