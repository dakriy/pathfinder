#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"

using namespace sf;

class Graphics
{
protected:
	std::vector<std::vector<int>> Maze;
	std::vector<RectangleShape *> squares;
	RenderWindow * window;
	Coordinate StartOfMaze;
	Coordinate EndOfMaze;
public:
	Graphics(std::vector<std::vector<int>> the_maze, Coordinate start, Coordinate end);
	void run();
	void update();
	void start();
	~Graphics();
};