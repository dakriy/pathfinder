#include <iostream>
#include <vector>
#include"Globals.h"
#include "PathFinder.h"
#include <SFML\System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

// This is the second's thread function.
void graphics(vector<vector<int>>  Maze);

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

	//Start the graphics
	sf::Thread graphics_thread(&graphics, Maze);
	graphics_thread.launch();

	Coordinate BeginMaze = Coordinate(0,0);
	Coordinate EndMaze = Coordinate(6,21);

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


	//Pauses Program
	system("PAUSE");

	//Ends Program
	return 0;
}

void graphics(vector<vector<int>>  Maze)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	int y = (Maze.size())*30;
	int x = (Maze[0].size())*30;
	sf::RenderWindow window(sf::VideoMode(x, y), "PathFinder", sf::Style::Default, settings);
	std::vector<sf::RectangleShape *> squares;
	for (int i = 0; i < Maze.size(); i++)
	{
		for (int z = 0; z < Maze[i].size(); z++)
		{
			sf::RectangleShape * nextRect = new sf::RectangleShape(sf::Vector2f(30, 30));
			nextRect->setOutlineColor(sf::Color(0, 191, 255));
			nextRect->setPosition(z * 30, i * 30);
			nextRect->setOutlineThickness(2);
			nextRect->setFillColor(sf::Color::Black);
			squares.push_back(nextRect);
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (int i = 0; i < squares.size(); i++)
		{
			window.draw(*squares[i]);
		}
		window.display();
	}
	for (int i = 0; i < squares.size(); i++)
	{
		delete squares[i];
	}
}