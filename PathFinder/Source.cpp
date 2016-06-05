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
	// MUSIC YAY! ^.^
	Music music;
	music.setLoop(true);
	music.setVolume(100);
	if (!music.openFromFile("Newton-Streamline.ogg"))
	{
		cout << "There was an error playing the song" << endl;
	}
	else
	{
		music.play();
	}

	// Path cycle speed in milliseconds. As in 1 every path_cycle_speed ms
	// NOTE: This does lock up the graphcs thread so don't put it too high or you won't be able to close graphics window
	// PS: too high would be like 1000. If you're under 500 you're okay.
	path_cycle_speed = 20;


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
		{ 0,1,0,0,0,0,0 },
		{ 0,1,0,1,1,1,0 },
		{ 0,1,1,1,0,1,1 },
		{ 0,0,0,0,0,0,1 },
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

	// This gets automatically deallocated when the program ends.
	Branch * Root = new Branch(BeginMaze);

	PathFinder MazeSolver = PathFinder(Maze, BeginMaze, EndMaze, Root);

	vector<Coordinate> Path;
	Path.push_back(BeginMaze);

	MazeSolver.BranchAll(BeginMaze, Path, Root);

	mutex.lock();
	final_path = MazeSolver.GetShortest(EndMaze);
	found_shortest_path = true;
	mutex.unlock();

	// Wait for thread to finish.
	// if thread gets killed before it finishes execution, thread cleanup will not occur
	graphics_thread.wait();
	// Delete the window object
	delete maze_gui;
	music.stop();
	//End Program
	return 0;
}