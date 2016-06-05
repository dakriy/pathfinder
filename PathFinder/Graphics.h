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
	// Declare and load a texture
	Texture sprite_sheet;
	Sprite Mouse;
	Sprite Cheese;
	int mouse_pos;

	void move_mouse_up();
	void move_mouse_down();
	void move_mouse_left();
	void move_mouse_right();
public:
	Graphics(std::vector<std::vector<int>> the_maze, Coordinate start, Coordinate end);
	void run();
	void update();
	void start();
	~Graphics();
};