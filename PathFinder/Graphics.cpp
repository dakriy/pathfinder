#include "Graphics.h"

Graphics::Graphics(std::vector<std::vector<int>> the_maze, Coordinate start, Coordinate end)
{
	this->Maze = the_maze;
	this->StartOfMaze = start;
	this->EndOfMaze = end;
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
	if (WorkerQueue.empty() && found_shortest_path)
	{
		mutex.lock();
		std::vector<Coordinate> path = final_path;
		mutex.unlock();
		int y = 0;
		int x = 0;
		for (int square_counter = 0; square_counter < squares.size(); square_counter++)
		{
			if (std::find(path.begin(), path.end(), Coordinate(x, y)) != path.end()) {
				squares[square_counter]->setFillColor(Color::Red);
			}
			else if (Maze[y][x] == 1)
			{
				squares[square_counter]->setFillColor(Color(211, 211, 211));
			}
			else
			{
				squares[square_counter]->setFillColor(Color::Black);
			}
			x++;
			if (x > 6)
			{
				y++;
				x = 0;
			}
		}
	}
	else
	{
		if (!WorkerQueue.empty())
		{
			mutex.lock();
			std::vector<Coordinate> path = WorkerQueue.front();
			WorkerQueue.pop();
			mutex.unlock();
			int y = 0;
			int x = 0;
			for (int square_counter = 0; square_counter < squares.size(); square_counter++)
			{
				if (std::find(path.begin(), path.end(), Coordinate(x, y)) != path.end()) {
					squares[square_counter]->setFillColor(Color::Red);
				}
				else if (Maze[y][x] == 1)
				{
					squares[square_counter]->setFillColor(Color(211, 211, 211));
				}
				else
				{
					squares[square_counter]->setFillColor(Color::Black);
				}
				x++;
				if (x > 6)
				{
					y++;
					x = 0;
				}
			}
		}
		else
		{
			// Copy and pasting code! WHEEEE
			int y = 0;
			int x = 0;
			for (int square_counter = 0; square_counter < squares.size(); square_counter++)
			{
				if (Maze[y][x] == 1)
				{
					squares[square_counter]->setFillColor(Color(211, 211, 211));
				}
				else
				{
					squares[square_counter]->setFillColor(Color::Black);
				}
				x++;
				if (x > 6)
				{
					y++;
					x = 0;
				}
			}
		}
	}
	for (int i = 0; i < squares.size(); i++)
	{
		window->draw(*squares[i]);
	}
	sleep(milliseconds(path_cycle_speed));
}

Graphics::~Graphics()
{
	delete this->window;
	for (int i = 0; i < this->squares.size(); i++)
	{
		delete this->squares[i];
	}
}
