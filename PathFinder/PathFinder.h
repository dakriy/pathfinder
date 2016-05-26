#pragma once
class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	//Coordinate[] GetShortestPath()
	//{
		//Return JD an array of coordinates of the shortest
		
	//}

	

protected:
	//Points to the left branch
	PathFinder* Left;

	//Points to the right branch
	PathFinder* Right;

	//Data defaults to negative 1
	int Data = -1;

	//Coordinate of the branch.
	Coordinate Pos = Coordinate();

};

