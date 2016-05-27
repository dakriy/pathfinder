#pragma once
#include <vector>


class PathFinder
{
public:
	PathFinder();

	PathFinder(std::vector<std::vector<int>> maze)
	{
		Maze = maze;
	}

	~PathFinder();

	std::vector<std::vector<int>> Maze;

	Coordinate Start;
	Coordinate End;

	std::vector<std::vector<Coordinate>> ShortCoord;
	
	PathFinder* Root;
	

	void BranchAll()
	{

		//Check all directions around coordinate

		//Check up of start
		

		//Check down of start

		//Check left of start

		//Check right of start

	}

	bool CheckValidCoordinates(Coordinate a)
	{
		if (a.X >= 0 && a.X <= ShortCoord[0].size())//Check column size
		{
			if (a.Y >= 0 && a.Y <= ShortCoord.size())//Check row size
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}

protected:
	//Points to the left branch
	PathFinder* Left = NULL;

	//Points to the right branch
	PathFinder* Right = NULL;

	//Data defaults to negative 1
	int Data = -1;

	//Coordinate of the branch.
	Coordinate Pos = Coordinate();

};

