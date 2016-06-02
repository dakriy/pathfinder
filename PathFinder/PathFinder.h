#pragma once
#include <vector>
#include "Globals.h"
#include<iostream>


class PathFinder
{
public:

	PathFinder(std::vector<std::vector<int>> maze, Coordinate start, Coordinate end);

	~PathFinder();

	std::vector<std::vector<int>> Maze;
	Coordinate StartOfMaze;
	Coordinate EndOfMaze;


	//2d Coordinate list of all method versions paths
	std::vector<std::vector<Coordinate>> AllPaths;
	
	//Run to find shortest path in maze! DANGER RECURSIVE!
	std::vector<Coordinate> BranchAll(Coordinate Start, std::vector<Coordinate> OldPath, Branch* StartingBranch);

	std::vector<Coordinate> GetShortest();

	//Checks if coordinates are indeed inside maze
	bool CheckValidCoordinates(Coordinate a);

};

