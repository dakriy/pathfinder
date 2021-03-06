#include "Graphics.h"

void Graphics::move_mouse_up()
{
	this->Mouse.move(0, -1);
	this->Mouse.setRotation(-90);
}

void Graphics::move_mouse_down()
{
	this->Mouse.move(0, 1);
	this->Mouse.setRotation(90);
}

void Graphics::move_mouse_left()
{
	this->Mouse.move(-1, 0);
	this->Mouse.setRotation(180);
}

void Graphics::move_mouse_right()
{
	this->Mouse.move(1, 0);
	this->Mouse.setRotation(0);
}

Graphics::Graphics(std::vector<std::vector<int>> the_maze, Coordinate start, Coordinate end)
{
	this->Maze = the_maze;
	this->StartOfMaze = start;
	this->EndOfMaze = end;
	this->sprite_sheet.loadFromFile("mouse_and_cheese_sprite.png");
	// Setup Mouse and Cheese
	Mouse.setTexture(this->sprite_sheet);
	Mouse.setTextureRect(IntRect(0, 10, 75, 42));
	this->Mouse.setScale(2.0 / 6.0, 3.0 / 6.0);
	this->Mouse.setPosition((this->StartOfMaze.X * 30)+15, (this->StartOfMaze.Y * 30)+15);
	this->Mouse.setOrigin(75 / 2, 42 / 2);
	Cheese.setTexture(this->sprite_sheet);
	Cheese.setTextureRect(IntRect(160, 8, 75, 50));
	this->Cheese.setScale(2.0 / 5.0, 3.0 / 5.0);
	this->Cheese.setPosition(this->EndOfMaze.X * 30, this->EndOfMaze.Y * 30);
}

void Graphics::start()
{
	// Thread setup that can't be done in constructor because contructor is initilaized in main thread.
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	// Set window height and length
	int y = (this->Maze.size()) * 30;
	int x = (this->Maze[0].size()) * 30;
	// Display the window
	this->window = new RenderWindow(VideoMode(x, y), "PathFinder", Style::Default, settings);
	// Make basic grid squares
	for (int i = 0; i < this->Maze.size(); i++)
	{
		for (int z = 0; z < Maze[i].size(); z++)
		{
			RectangleShape * nextRect = new RectangleShape(Vector2f(30, 30));
			nextRect->setOutlineColor(Color(0, 191, 255));
			nextRect->setPosition(z * 30, i * 30);
			nextRect->setOutlineThickness(2);
			nextRect->setFillColor(Color::Black);
			this->squares.push_back(nextRect);
		}
	}

	// Run the window
	this->run();
}

void Graphics::run()
{
	while (window->isOpen())
	{
		Event event;
		// Watch for window close
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		window->clear();
		this->update();
		window->display();
	}
}


void Graphics::update()
{
	bool draw_cheese = true;
	// if there are no new paths and we have found the shortest path
	if (WorkerQueue.empty() && found_shortest_path)
	{
		// get shortest path
		mutex.lock();
		std::vector<Coordinate> path = final_path;
		mutex.unlock();
		int y = 0;
		int x = 0;
		
		// Print out maze with final path
		for (int square_counter = 0; square_counter < squares.size(); square_counter++)
		{
			// If current square is in the final path paint it red
			if (std::find(path.begin(), path.end(), Coordinate(x, y)) != path.end()) {
				squares[square_counter]->setFillColor(Color::Red);
			}
			// if it's not in the final path but it's still a moveable tile paint it greyish
			else if (Maze[y][x] == 1)
			{
				squares[square_counter]->setFillColor(Color(211, 211, 211));
			}
			else
			{
				// if it's not apart of the maze make it black
				squares[square_counter]->setFillColor(Color::Black);
			}
			x++;
			if (x == Maze[0].size())
			{
				y++;
				x = 0;
			}
		}
		// Deal with moving the mouse
		if (mouse_pos < path.size())
		{
			if(this->Mouse.getPosition().x < (path[mouse_pos].X*30)+15)
			{
				this->move_mouse_right();
			}
			else if (this->Mouse.getPosition().x > (path[mouse_pos].X * 30)+15)
			{
				this->move_mouse_left();
			}
			else if (this->Mouse.getPosition().y < (path[mouse_pos].Y * 30)+15)
			{
				this->move_mouse_down();
			}
			else if (this->Mouse.getPosition().y > (path[mouse_pos].Y * 30)+15)
			{
				this->move_mouse_up();
			}
			else if (this->Mouse.getPosition().x == (path[mouse_pos].X * 30)+15 && this->Mouse.getPosition().y == (path[mouse_pos].Y * 30)+15)
			{
				mouse_pos++;
			}
		}
		// if the mouse has reached the cheese don't draw the cheese
		else
		{
			draw_cheese = false;
		}
		// Draw squares on screen
		for (int i = 0; i < squares.size(); i++)
		{
			window->draw(*squares[i]);
		}
		// Wait for next mouse movement
		sleep(milliseconds(20));
	}
	else
	{
		// If there's new paths
		if (!WorkerQueue.empty())
		{
			// get the path
			mutex.lock();
			std::vector<Coordinate> path = WorkerQueue.front();
			WorkerQueue.pop();
			mutex.unlock();
			int y = 0;
			int x = 0;
			// start displaying tiles
			for (int square_counter = 0; square_counter < squares.size(); square_counter++)
			{
				// if the tile is in the solution path make it red
				if (std::find(path.begin(), path.end(), Coordinate(x, y)) != path.end()) {
					squares[square_counter]->setFillColor(Color::Red);
				}
				//  if it's not apart of the solution path but apart of the maze make it greyish
				else if (Maze[y][x] == 1)
				{
					squares[square_counter]->setFillColor(Color(211, 211, 211));
				}
				// otherwise make it black
				else
				{
					squares[square_counter]->setFillColor(Color::Black);
				}
				// counter for syncronizing the linear square vector and the nonlinear maze vector
				x++;
				if (x == Maze[0].size())
				{
					y++;
					x = 0;
				}
			}
		}
		// wait to get next path
		sleep(milliseconds(path_cycle_speed));
		for (int i = 0; i < squares.size(); i++)
		{
			window->draw(*squares[i]);
		}
	}
	// if the mouse hasn't gotten to the cheese draw it
	if (draw_cheese)
	{
		window->draw(Cheese);
	}
	window->draw(Mouse);
}

Graphics::~Graphics()
{
	// deallocate memory
	delete this->window;
	for (int i = 0; i < this->squares.size(); i++)
	{
		delete this->squares[i];
	}
}
