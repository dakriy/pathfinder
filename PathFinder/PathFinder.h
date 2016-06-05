#pragma once
#include "Globals.h"


class PathFinder
{
protected:
	Branch * TreeRoot;
	//2d Coordinate list of all method versions paths
	std::vector<std::vector<Coordinate>> AllPaths;
	std::vector<std::vector<int>> Maze;
	Coordinate StartOfMaze;
	Coordinate EndOfMaze;
public:
	PathFinder(std::vector<std::vector<int>> maze, Coordinate start, Coordinate end, Branch * Root);
	bool NavDeepDelete(Branch *Check);
	std::vector<Coordinate> GetShortest(Coordinate EndOfMaze);
	bool PathContains(Coordinate a, std::vector<Coordinate> b);
	void PathFinder::BranchAll(Coordinate Start, std::vector<Coordinate> OldPath, Branch* StartingBranch);
	//Checks if coordinates are indeed inside maze
	bool CheckValidCoordinates(Coordinate a);
	~PathFinder();
};

