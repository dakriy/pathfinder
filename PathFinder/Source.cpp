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
	Coordinate EndMaze = Coordinate(4,9);

	PathFinder A = PathFinder(Maze, BeginMaze, EndMaze);

	
	Branch Root(BeginMaze);

	Branch *RealRoot = &Root;

	vector<Coordinate> Path;
	Path.push_back(BeginMaze);

	A.BranchAll(BeginMaze, Path, RealRoot);

	Path = A.GetShortest();

	cout << Path.size() << endl;

	//Display Path!
	for (int i = 0; i < Path.size(); i++)
	{
		cout << "X: " << Path[i].X << "Y: " << Path[i].Y << endl;
	}


	//Pauses Program
	system("PAUSE");

	//Ends Program
	return 0;
}