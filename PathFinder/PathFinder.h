#pragma once
#include <vector>
#include "Globals.h"
#include<iostream>


class PathFinder
{
public:
	PathFinder();

	PathFinder(std::vector<std::vector<int>> maze,Coordinate start, Coordinate end)
	{
		Maze = maze;
		StartOfMaze = start;
		EndOfMaze = end;
	}

	~PathFinder();

	std::vector<std::vector<int>> Maze;
	Coordinate StartOfMaze;
	Coordinate EndOfMaze;

	//Vector list of count sizes
	std::vector<int> PathSizes;

	//Root
	Branch Root = Branch();
	

	//2d Coordinate list of all method versions paths
	std::vector<std::vector<Coordinate>> AllPaths;
	
	//Run to find shortest path in maze! DANGER RECURSIVE!
	std::vector<Coordinate> BranchAll(Coordinate Start,std::vector<Coordinate> OldPath, Branch* StartingBranch)
	{
		std::cout << "RUN!" << std::endl;
		std::cout << "X:" << Start.X << "Y:" << Start.Y << std::endl;
		bool Continue = true;

		//CoordList of this versions path
		std::vector<Coordinate> Path = OldPath;

		//Actually add coordinates to the path...
		Path.push_back(Start);

		//SYNTAX!!!
		//Check that this has not already been visited, if it has it will stop adding paths and return what it has
		int TimesVisited = 0;
		for (int i = 0; i < Path.size(); i++)
		{
			if (Path[i].X == Start.X && Path[i].Y == Start.Y)
			{
				TimesVisited++;
			}
		}

		//Efficiency possibly improved here?
		if (TimesVisited > 2)
		{
			Continue = false;
			std::cout << "CONTINUE TO:" << Continue << std::endl;
		}

		std::cout << "Times Visited:"<< TimesVisited << std::endl;
		

		//Check it's not at the end!
		if (Start.X != EndOfMaze.X && Start.Y != EndOfMaze.Y && Continue == true)
		{
			std::cout << "CONTINUE IS:" << Continue << std::endl;

			//Check all directions around coordinate
			//Check up of start
			//Begin New Branch with coordinate in it
			StartingBranch->Left = &Branch();

			//Check up of start; Check if block above start is valid (within maze) then checks if it is enterable or not
			

			//ERROR BETWEEN THIS ^ AND 2! ;D
			if (CheckValidCoordinates(Coordinate(Start.X, Start.Y + 1)) == true && Maze[Start.Y + 1][Start.X] == 1)
			{

					//Is enterable
					StartingBranch->Left->Data = 1;

					
					//Begin Again!
					AllPaths.push_back(BranchAll(Coordinate(Start.X, Start.Y + 1), Path, StartingBranch->Left));
					
			}
			else
			{
				StartingBranch->Left->Data = 0;
			}


			//Check down of start
			//Begin New Branch with coordinate in it
			StartingBranch->Right = &Branch();

			//Check up of start; Check if block above start is valid (within maze) then checks if it is enterable or not
			if (CheckValidCoordinates(Coordinate(Start.X, Start.Y - 1)) == true && Maze[Start.Y - 1][Start.X] == 1)
			{
				//Is enterable
				StartingBranch->Right->Data = 1;

				//Begin Again!
				AllPaths.push_back(BranchAll(Coordinate(Start.X, Start.Y - 1), Path,StartingBranch->Right));

			}
			else
			{
				StartingBranch->Right->Data = 0;
			}




			//Check left of start

			//Begin New Branch with coordinate in it
			StartingBranch->Left->Left = &Branch();

			if (CheckValidCoordinates(Coordinate(Start.X - 1, Start.Y)) == true && Maze[Start.Y][Start.X - 1] == 1)
			{
				//Is enterable
				StartingBranch->Left->Left->Data = 1;

				//Begin Again!
				AllPaths.push_back(BranchAll(Coordinate(Start.X - 1, Start.Y), Path, StartingBranch->Left->Left));
			}
			else
			{
				StartingBranch->Left->Left->Data = 0;
			}

			//Check right of start
			StartingBranch->Right->Right = &Branch();

			if (CheckValidCoordinates(Coordinate(Start.X + 1, Start.Y)) == true && Maze[Start.Y][Start.X + 1] == 1)
			{
				//Is enterable
				StartingBranch->Right->Right->Data = 1;

				//Begin Again!
				AllPaths.push_back(BranchAll(Coordinate(Start.X + 1, Start.Y), Path, StartingBranch->Right->Right));
			}
			else
			{
				StartingBranch->Right->Right->Data = 0;
			}

		}
		else
		{
			return Path;
		}
	}

	std::vector<Coordinate> GetShortest()
	{
		int PositionOfShortest = 0;
		std::vector<Coordinate> Shortest;

		for (int y = 0; y < AllPaths.size(); y++)
		{
			for (int x = 0; x < AllPaths[y].size();  x++)
			{
				if (Shortest.size() == 0)
				{

				}
				else if (AllPaths[y].size() < Shortest.size())
				{
					Shortest = AllPaths[y];
				}
			}
		}

		return Shortest;

	}

	//Checks if coordinates are indeed inside maze
	bool CheckValidCoordinates(Coordinate a)
	{
		//Make sure Maze[0] actually exists first ^_^
		if (Maze.size() > 0)
		{
			if (a.X >= 0 && a.X <= Maze[0].size())//Check column size
			{
				std::cout << "Comparing X:" << a.X << " to maze max of " << Maze[0].size() << std::endl;
				if (a.Y >= 0 && a.Y <= Maze.size())//Check row size
				{
					std::cout << "Comparing Y:" << a.Y << " to maze max of " << Maze.size() << std::endl;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}



};

