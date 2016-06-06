#include <iostream>
#include <vector>
#include"Globals.h"
#include "PathFinder.h"
#include <SFML/System.hpp>
#include "Graphics.h"
#include <SFML/Audio.hpp>
#include <fstream>

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

	cout << "Enter the path cycle speed in milliseconds. (How long to stay on one path)" << endl;
	// Path cycle speed in milliseconds. As in 1 every path_cycle_speed ms
	// NOTE: This does lock up the graphcs thread so don't put it too high or you won't be able to close graphics window
	// PS: too high would be like 1000. If you're under 500 you're okay.
	cin >> path_cycle_speed;
	cout << "Enter the file name for the maze " << endl;
	string file_path;
	cin >> file_path;
	ifstream file(file_path, ios::in | ios::binary | ios::ate);
	int x;
	int y;
	Coordinate BeginMaze;
	Coordinate EndMaze;
	vector<vector<int>>  Maze;
	if (file.is_open())
	{
		file.seekg(0, ios::beg);
		file.read((char *)&x, sizeof(x));
		file.read((char *)&y, sizeof(y));
		file.read((char *)&BeginMaze, sizeof(BeginMaze));
		file.read((char *)&EndMaze, sizeof(EndMaze));
		for (int i = 0; i < y; i++)
		{
			vector<int> tempx;
			for (int z = 0; z < x; z++)
			{
				int temp_var;
				file.read((char *)&temp_var, sizeof(temp_var));
				tempx.push_back(temp_var);
			}
			Maze.push_back(tempx);
		}
	}
	else
	{
		cout << "Could not find file. Exiting" << endl;
		system("pause");
		music.stop();
		return -1;
	}



	/*vector<vector<int>>  Maze = //Y //X
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
	};*/

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