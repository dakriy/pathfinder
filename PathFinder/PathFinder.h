#pragma once
#include <vector>
#include "Globals.h"
#include<iostream>


class PathFinder
{
protected:
	Branch * TreeRoot;
public:
	PathFinder(std::vector<std::vector<int>> maze, Coordinate start, Coordinate end, Branch * Root);


	std::vector<std::vector<int>> Maze;
	Coordinate StartOfMaze;
	Coordinate EndOfMaze;

	//2d Coordinate list of all method versions paths
	std::vector<std::vector<Coordinate>> AllPaths;


	bool NavDeepDelete(Branch *Check);

	std::vector<Coordinate> GetShortest(Coordinate EndOfMaze);

	bool PathContains(Coordinate a, std::vector<Coordinate> b);

	//Run to find shortest path in maze! DANGER RECURSIVE!
	//std::vector<Coordinate*> BranchAll(Coordinate Start, std::vector<Coordinate*> OldPath, Branch* StartingBranch);
	
	void PathFinder::BranchAll(Coordinate Start, std::vector<Coordinate> OldPath, Branch* StartingBranch);

	
	//Checks if coordinates are indeed inside maze
	bool CheckValidCoordinates(Coordinate a);
	~PathFinder();
};

