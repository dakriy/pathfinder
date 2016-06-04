#include "PathFinder.h"
#include "Globals.h"

PathFinder::~PathFinder()
{
	this->NavDeepDelete(this->TreeRoot);
}

bool PathFinder::NavDeepDelete(Branch *Check)
{
	if (Check)
	{
		if(
			this->NavDeepDelete(Check->Up) && 
			this->NavDeepDelete(Check->Down) && 
			this->NavDeepDelete(Check->Left) && 
			this->NavDeepDelete(Check->Right)
			)
		{
			delete Check;
			return true;
		}
		return false;
	}
	else
	{
		return true;
	}
}

PathFinder::PathFinder(std::vector<std::vector<int>> maze, Coordinate start, Coordinate end, Branch * Root)
{
	Maze = maze;
	StartOfMaze = start;
	EndOfMaze = end;
	this->TreeRoot = Root;
}


void PathFinder::BranchAll(Coordinate Start, std::vector<Coordinate> OldPath, Branch* StartingBranch)
{
	//system("PAUSE");
	//std::cout << "RUN!" << std::endl;
	//std::cout << "X:" << Start.X << "Y:" << Start.Y << "  ACTUAL" << std::endl;
	//std::cout << "X Check: " << EndOfMaze.X << " Y Check: " << EndOfMaze.Y << std::endl;
	//std::cout << "All Paths Size: " << AllPaths.size() << std::endl;


	//CoordList of this versions path
	std::vector<Coordinate> Path = OldPath;

	for (int i = 0; i < Path.size(); i++)
	{
		//std::cout << "(" << Path[i].X << "," << Path[i].Y << ")" << std::endl;
	}

	//Actually add coordinates to the path...
	Path.push_back(Start);



		//Check it's not at the end!

				//Create New Branches Everywhere! 

				//Check all directions around coordinate
				//Check up of start


				//Check up of start; Check if block above start is valid (within maze) then checks if it is enterable or not
				if (CheckValidCoordinates(Coordinate(Start.X, Start.Y + 1)) == true && Maze[Start.Y + 1][Start.X] == 1)
				{
					if (PathContains(Coordinate(Start.X, Start.Y + 1), Path) == false)
					{
						//Begin New Branch with coordinate in it
						Branch *Up = new Branch(Coordinate(Start.X, Start.Y + 1));
						StartingBranch->Up = Up;


						//Is enterable
						StartingBranch->Up->Data = 1;


						//Begin Again!
						BranchAll(Coordinate(Start.X, Start.Y + 1), Path, StartingBranch->Up);
					}
				}


				//Check down of start

				//Check up of start; Check if block above start is valid (within maze) then checks if it is enterable or not
				if (CheckValidCoordinates(Coordinate(Start.X, Start.Y - 1)) == true && Maze[Start.Y - 1][Start.X] == 1)
				{

					if (PathContains(Coordinate(Start.X, Start.Y - 1), Path) == false)
					{
						//Begin New Branch with coordinate in it
						Branch *Down = new Branch(Coordinate(Start.X, Start.Y - 1));
						StartingBranch->Down = Down;


						//Is enterable
						StartingBranch->Down->Data = 1;



						//Begin Again!
						BranchAll(Coordinate(Start.X, Start.Y - 1), Path, StartingBranch->Down);

					}
				}

				//Check left of start
				if (CheckValidCoordinates(Coordinate(Start.X - 1, Start.Y)) == true && Maze[Start.Y][Start.X - 1] == 1)
				{
					if (PathContains(Coordinate(Start.X - 1, Start.Y), Path) == false)
					{
						//Begin New Branch with coordinate in it
						Branch *Left = new Branch(Coordinate(Start.X - 1, Start.Y));
						StartingBranch->Left = Left;

						//Is enterable
						StartingBranch->Left->Data = 1;

						//Begin Again!
						BranchAll(Coordinate(Start.X - 1, Start.Y), Path, StartingBranch->Left);
					}

				}


				//Check right of start
				if (CheckValidCoordinates(Coordinate(Start.X + 1, Start.Y)) == true && Maze[Start.Y][Start.X + 1] == 1)
				{
					if (PathContains(Coordinate(Start.X + 1, Start.Y), Path) == false)
					{
						//Begin New Branch with coordinate in it 
						Branch *Right = new Branch(Coordinate(Start.X + 1, Start.Y));
						StartingBranch->Right = Right;

						//Is enterable
						StartingBranch->Right->Data = 1;

						//Begin Again!
						BranchAll(Coordinate(Start.X + 1, Start.Y), Path, StartingBranch->Right);
					}
				}

				if (PathContains(EndOfMaze, Path) == true)
				{
					AllPaths.push_back(Path);
				}


	
}



//Run to find shortest path in maze! DANGER RECURSIVE!

/*
std::vector<Coordinate*> BranchAll(Coordinate Start, std::vector<Coordinate*> OldPath, Branch* StartingBranch)
{



	std::cout << "RUN!" << std::endl;
	std::cout << "X:" << Start.X << "Y:" << Start.Y << "  ACTUAL" << std::endl;
	std::cout << "All Paths Size: " << AllPaths.size() << std::endl;
	bool Continue = true;

	//CoordList of this versions path
	std::vector<Coordinate*> Path;

	for (int i = 0; i < OldPath.size(); i++)
	{
		Path.push_back(OldPath[i]);
	}

	//Actually add coordinates to the path...
	Path.push_back(&Start);

	//SYNTAX!!!
	//Check that this has not already been visited, if it has it will stop adding paths and return what it has
	int TimesVisited = 0;
	for (int i = 0; i < Path.size(); i++)
	{
		if (Path[i]->X == Start.X && Path[i]->Y == Start.Y)
		{
			TimesVisited++;
		}
	}

	//Efficiency possibly improved here?
	if (TimesVisited > 3)
	{
		std::cout << "No Continue Granted!" << std::endl;

		return Path;
	}



	//Check it's not at the end!
	if (Start.X != EndOfMaze.X && Start.Y != EndOfMaze.Y)
	{
		//Create New Branches Everywhere! 

		//Begin New Branch with coordinate in it
		Branch *Up = new Branch(Coordinate(Start.X, Start.Y + 1));
		StartingBranch->Up = Up;

		//Begin New Branch with coordinate in it
		Branch *Down = new Branch(Coordinate(Start.X, Start.Y - 1));
		StartingBranch->Down = Down;


		//Begin New Branch with coordinate in it
		Branch *Left = new Branch(Coordinate(Start.X - 1, Start.Y));
		StartingBranch->Left = Left;

		//Begin New Branch with coordinate in it 
		Branch *Right = new Branch(Coordinate(Start.X + 1, Start.Y));
		StartingBranch->Right = Right;

		if (Up == NULL || Down == NULL || Left == NULL || Right == NULL)
		{
			std::cout << "ERROR!!!!! ERMGAGHERD ITS NULL!!!!!!!" << std::endl;
		}

		//Check all directions around coordinate
		//Check up of start

		//Check up of start; Check if block above start is valid (within maze) then checks if it is enterable or not
		if (CheckValidCoordinates(Coordinate(Start.X, Start.Y + 1)) == true && Maze[Start.Y + 1][Start.X] == 1)
		{

			//Is enterable
			StartingBranch->Up->Data = 1;


			//Begin Again!
			AllPaths.push_back(BranchAll(Coordinate(Start.X, Start.Y + 1), Path, StartingBranch->Up));

		}


		//Check down of start

		//Check up of start; Check if block above start is valid (within maze) then checks if it is enterable or not
		if (CheckValidCoordinates(Coordinate(Start.X, Start.Y - 1)) == true && Maze[Start.Y - 1][Start.X] == 1)
		{




			//Is enterable
			StartingBranch->Down->Data = 1;

			
			Another classic case is having a bad "this" pointer, usually NULL or a low value.
			That happens when the object reference on which you call the method is bad.
			The method will run as usual but blow up as soon as it tries to access a class member.
			Again, heap corruption or using a pointer that was deleted will cause this.
			Good luck debugging this; it is never easy.
			

			//Begin Again!
			AllPaths.push_back(BranchAll(Coordinate(Start.X, Start.Y - 1), Path, StartingBranch->Down));


		}



		//Check left of start
		if (CheckValidCoordinates(Coordinate(Start.X - 1, Start.Y)) == true && Maze[Start.Y][Start.X - 1] == 1)
		{


			//Is enterable
			StartingBranch->Left->Data = 1;

			//std::cout << "AllPaths[AllPaths.size()].size() = " << AllPaths[AllPaths.size()].size() << std::endl;
			//std::cout << "AllPaths.size() = " << AllPaths.size() << std::endl;

			//Begin Again!
			std::vector<Coordinate*> Returner = BranchAll(Coordinate(Start.X - 1, Start.Y), Path, StartingBranch->Left);

			Returner.size();

			AllPaths.push_back(Returner);
		}


		//Check right of start
		if (CheckValidCoordinates(Coordinate(Start.X + 1, Start.Y)) == true && Maze[Start.Y][Start.X + 1] == 1)
		{


			//Is enterable
			StartingBranch->Right->Data = 1;

			//Begin Again!
			AllPaths.push_back(BranchAll(Coordinate(Start.X + 1, Start.Y), Path, StartingBranch->Right));
		}



	}
	else
	{
		std::cout << "Returning Path Size of: " << Path.size() << std::endl;


		for (int i = 0; i < Path.size(); i++)
		{
			std::cout << "X:" << Path[i]->X << "Y:" << Path[i]->Y << std::endl;
			std::cout << "Number: " << i << " of a total of " << Path.size() << std::endl;
		}

		//Return Psuedo Path

		return Path;

	}
}*/



std::vector<Coordinate> PathFinder::GetShortest(Coordinate EndOfMaze)
{
	std::vector<Coordinate> Shortest;

	Shortest = AllPaths[0];

	for (int y = 0; y < AllPaths.size(); y++)
	{
		for (int x = 0; x < AllPaths[y].size(); x++)
		{
			if (AllPaths[y][x].X == EndOfMaze.X && AllPaths[y][x].Y == EndOfMaze.Y)
			{
				if (Shortest.size() >= AllPaths[y].size())
				{
					Shortest = AllPaths[y];
				}
			}
		}
	}

	return Shortest;
}

//Checks if coordinates are indeed inside maze
bool PathFinder::CheckValidCoordinates(Coordinate a)
{
	//Make sure Maze[0] actually exists first ^_^
	if (Maze.size() > 0)
	{
		if (a.X >= 0 && a.X <= Maze[0].size() - 1)//Check column size
		{
			//std::cout << "Comparing X:" << a.X << " to maze max of " << Maze[0].size() << std::endl;
			if (a.Y >= 0 && a.Y <= Maze.size() - 1)//Check row size
			{
				//std::cout << "Comparing Y:" << a.Y << " to maze max of " << Maze.size() << std::endl;
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool PathFinder::PathContains(Coordinate a,std::vector<Coordinate> b)
{
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i].X == a.X)
		{
			if (b[i].Y == a.Y)
			{
				return true;
			}
		}
	}

	return false;
}