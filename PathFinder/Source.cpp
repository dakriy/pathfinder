#include <iostream>
#include <vector>
#include"Globals.h"
#include "PathFinder.h"
#include <SFML/System.hpp>
#include "Graphics.h"
#include <SFML/Audio.hpp>

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

	Coordinate BeginMaze = Coordinate(0, 0);
	Coordinate EndMaze = Coordinate(6, 21);

	// Setup a new graphics object
	Graphics * maze_gui = new Graphics(Maze, BeginMaze, EndMaze);

	// Create thread to run the window
	Thread graphics_thread(&Graphics::start, maze_gui);
	// start thread and start displaying
	graphics_thread.launch();

	Music music;
	music.setLoop(true);
	music.setVolume(50);
	if (!music.openFromFile("Newton-Streamline.ogg"))
	{
		cout << "There was an error playing the song" << endl;
	}
	else
	{
		music.play();
	}
	// This gets automatically deallocated when the program ends.
	Branch * Root = new Branch(BeginMaze);

	PathFinder MazeSolver = PathFinder(Maze, BeginMaze, EndMaze, Root);

	vector<Coordinate> Path;
	Path.push_back(BeginMaze);

	MazeSolver.BranchAll(BeginMaze, Path, Root);

	Path = MazeSolver.GetShortest(EndMaze);

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

	cout << endl;
	//Pauses Program
	system("PAUSE");

	// Wait for thread to finish.
	// if thread gets killed before it finishes execution, thread cleanup will not occur
	graphics_thread.wait();
	// Delete the window object
	delete maze_gui;
	music.stop();
	//End Program
	return 0;
}