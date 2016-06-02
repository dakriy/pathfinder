#include "PathFinder.h"
#include "Globals.h"


PathFinder::PathFinder(std::vector<std::vector<int>> maze, Coordinate start, Coordinate end)
{
	Maze = maze;
	StartOfMaze = start;
	EndOfMaze = end;
}


std::vector<Coordinate> PathFinder::BranchAll(Coordinate Start, std::vector<Coordinate> OldPath, Branch* StartingBranch)
{
	std::cout << "RUN!" << std::endl;
	std::cout << "X:" << Start.X << "Y:" << Start.Y << std::endl;
	std::cout << AllPaths.size() << std::endl;
	bool Continue = true;

	//CoordList of this versions path
	std::vector<Coordinate> Path;
	Path.swap(OldPath);//duplicates

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
		return Path;
	}


	//Check it's not at the end!
	if (Start.X != EndOfMaze.X && Start.Y != EndOfMaze.Y)
	{

		//Check all directions around coordinate
		//Check up of start


		//Check up of start; Check if block above start is valid (within maze) then checks if it is enterable or not

		if (CheckValidCoordinates(Coordinate(Start.X, Start.Y + 1)) == true && Maze[Start.Y + 1][Start.X] == 1)
		{
			//Begin New Branch with coordinate in it
			StartingBranch->Left = new Branch(Coordinate(Start.X, Start.Y + 1));

			//Is enterable
			StartingBranch->Left->Data = 1;


			//Begin Again!
			std::cout << "Got to left" << std::endl;
			AllPaths.push_back(BranchAll(Coordinate(Start.X, Start.Y + 1), Path, StartingBranch->Left));

		}
		else if (CheckValidCoordinates(Coordinate(Start.X, Start.Y + 1)) == true && Maze[Start.Y + 1][Start.X] == 0)
		{
			//Begin New Branch with coordinate in it
			StartingBranch->Left = new Branch(Coordinate(Start.X, Start.Y + 1));

			StartingBranch->Left->Data = 0;
		}



		//Check down of start

		std::cout << "X:" << Start.X << "Y:" << Start.Y << std::endl;

		//Check up of start; Check if block above start is valid (within maze) then checks if it is enterable or not
		if (CheckValidCoordinates(Coordinate(Start.X, Start.Y - 1)) == true && Maze[Start.Y - 1][Start.X] == 1)
		{
			//Begin New Branch with coordinate in it
			StartingBranch->Right = new Branch(Coordinate(Start.X, Start.Y - 1));

			//Is enterable
			StartingBranch->Right->Data = 1;

			/*
			Another classic case is having a bad "this" pointer, usually NULL or a low value.
			That happens when the object reference on which you call the method is bad.
			The method will run as usual but blow up as soon as it tries to access a class member.
			Again, heap corruption or using a pointer that was deleted will cause this.
			Good luck debugging this; it is never easy.
			*/

			if (StartingBranch->Right == NULL)
			{
				std::cout << "ERROR!!!!" << std::endl;
			}
			else
			{
				std::cout << "Checked." << std::endl;
			}

			//Begin Again!
			std::cout << "Got to right" << std::endl;
			AllPaths.push_back(this->BranchAll(Coordinate(Start.X, Start.Y - 1), Path, StartingBranch->Right));



		}
		else if (CheckValidCoordinates(Coordinate(Start.X, Start.Y - 1)) == true && Maze[Start.Y + 1][Start.X] == 0)
		{
			//Begin New Branch with coordinate in it
			StartingBranch->Right = new Branch(Coordinate(Start.X, Start.Y - 1));

			StartingBranch->Right->Data = 0;
		}



		//Check left of start



		if (CheckValidCoordinates(Coordinate(Start.X - 1, Start.Y)) == true && Maze[Start.Y][Start.X - 1] == 1)
		{
			//Begin New Branch with coordinate in it
			StartingBranch->Left->Left = new Branch(Coordinate(Start.X - 1, Start.Y));

			//Is enterable
			StartingBranch->Left->Left->Data = 1;

			//Begin Again!
			AllPaths.push_back(BranchAll(Coordinate(Start.X - 1, Start.Y), Path, StartingBranch->Left->Left));
		}
		else if (CheckValidCoordinates(Coordinate(Start.X - 1, Start.Y)) == true && Maze[Start.Y + 1][Start.X] == 0)
		{
			//Begin New Branch with coordinate in it
			StartingBranch->Left->Left = new Branch(Coordinate(Start.X - 1, Start.Y));

			StartingBranch->Left->Left->Data = 0;
		}



		if (CheckValidCoordinates(Coordinate(Start.X + 1, Start.Y)) == true && Maze[Start.Y][Start.X + 1] == 1)
		{
			//Check right of start
			StartingBranch->Right->Right = new Branch(Coordinate(Start.X + 1, Start.Y));

			//Is enterable
			StartingBranch->Right->Right->Data = 1;

			//Begin Again!
			AllPaths.push_back(BranchAll(Coordinate(Start.X + 1, Start.Y), Path, StartingBranch->Right->Right));
		}
		else if (CheckValidCoordinates(Coordinate(Start.X + 1, Start.Y)) == true && Maze[Start.Y + 1][Start.X] == 0)
		{
			//Begin New Branch with coordinate in it
			StartingBranch->Right->Right = new Branch(Coordinate(Start.X + 1, Start.Y));

			StartingBranch->Right->Right->Data = 0;
		}

	}
	else
	{
		std::cout << "Returning Path Size of: " << Path.size() << std::endl;
		return Path;
	}
}


std::vector<Coordinate> PathFinder::GetShortest()
{
	int PositionOfShortest = 0;
	std::vector<Coordinate> Shortest;

	for (int y = 0; y < AllPaths.size(); y++)
	{
		for (int x = 0; x < AllPaths[y].size(); x++)
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

bool PathFinder::CheckValidCoordinates(Coordinate a)
{
	//Make sure Maze[0] actually exists first ^_^
	if (Maze.size() > 0)
	{
		if (a.X >= 0 && a.X <= Maze[0].size() - 1)//Check column size
		{
			std::cout << "Comparing X:" << a.X << " to maze max of " << Maze[0].size() << std::endl;
			if (a.Y >= 0 && a.Y <= Maze.size() - 1)//Check row size
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


PathFinder::~PathFinder()
{
}
