#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

using namespace sf;


struct Coordinate
{

	Coordinate(int x = 0, int y = 0)
	{
		X = x;
		Y = y;
	}

	int X;
	int Y;

	bool operator==(Coordinate a) const
	{
		if (a.X == X && a.Y == Y)
			return true;
		else
			return false;
	}

};


int main()
{
	bool handled_square = false;
	float square_x = -1;
	float square_y = -1;
	bool draw_mouse = false;
	bool draw_cheese = false;
	Coordinate * startCoord = new Coordinate();
	Coordinate * endCoord = new Coordinate();
	int x;
	int y;
	std::cout << "How many squares in the x direction do you want?" << std::endl;
	std::cin >> x;
	std::cout << "How many squares in the y direction do you want?" << std::endl;
	std::cin >> y;
	std::cout << "Right click to set start point. Middle click to set end point." << std::endl;
	std::cout << "Single left click to create maze place" << std::endl;
	std::cout << "Close to save" << std::endl;
	
	std::vector<RectangleShape *> squares;



	ContextSettings settings;
	settings.antialiasingLevel = 8;
	// Set window height and length
	// Display the window
	RenderWindow window(VideoMode(x * 30, y * 30), "PathMaker", Style::Default, settings);
	// Make basic grid squares
	for (int i = 0; i < y; i++)
	{
		for (int z = 0; z < x; z++)
		{
			RectangleShape * nextRect = new RectangleShape(Vector2f(30, 30));
			nextRect->setOutlineColor(Color(0, 191, 255));
			nextRect->setPosition(z * 30, i * 30);
			nextRect->setOutlineThickness(2);
			nextRect->setFillColor(Color::Black);
			squares.push_back(nextRect);
		}
	}

	std::vector<std::vector<int>> *maze = new std::vector<std::vector<int>>;

	std::vector<int> temp;
	for (int i = 0; i < x; i++)
	{
		temp.push_back(0);
	}

	for (int i = 0; i < y; i++)
	{
		(*maze).push_back(temp);
	}

	Sprite Mouse;
	Sprite Cheese;
	Texture sprite_sheet;
	sprite_sheet.loadFromFile("mouse_and_cheese_sprite.png");

	Mouse.setTexture(sprite_sheet);
	Mouse.setTextureRect(IntRect(0, 8, 75, 42));
	Mouse.setScale(2.0 / 6.0, 3.0 / 6.0);
	Cheese.setTexture(sprite_sheet);
	Cheese.setTextureRect(IntRect(160, 8, 75, 50));
	Cheese.setScale(2.0 / 5.0, 3.0 / 5.0);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		if (Mouse::getPosition(window).x < window.getSize().x && Mouse::getPosition(window).y < window.getSize().y && Mouse::getPosition(window).x > 0 && Mouse::getPosition(window).y > 0)
		{
			if (Mouse::isButtonPressed(Mouse::Button::Left))
			{
				int a = 0;
				int b = 0;
				for (int i = 0; i < squares.size(); i++)
				{
					if (squares[i]->getPosition().x < Mouse::getPosition(window).x && squares[i]->getPosition().x + 30 > Mouse::getPosition(window).x && squares[i]->getPosition().y < Mouse::getPosition(window).y && squares[i]->getPosition().y + 30 > Mouse::getPosition(window).y)
					{
						if (squares[i]->getPosition().x == square_x && squares[i]->getPosition().y == square_y && handled_square)
						{
							break;
						}
						square_x = squares[i]->getPosition().x;
						square_y = squares[i]->getPosition().y;
						handled_square = true;
						if ((*maze)[b][a] == 0)
						{
							(*maze)[b][a] = 1;
							squares[i]->setFillColor(Color(211, 211, 211));
						}
						else
						{
							(*maze)[b][a] = 0;
							squares[i]->setFillColor(Color::Black);
						}
						break;
					}

					a++;
					if (a == x)
					{
						b++;
						a = 0;
					}
				}
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Middle))
			{
				int a = 0;
				int b = 0;
				for (int i = 0; i < squares.size(); i++)
				{
					if (squares[i]->getPosition().x < Mouse::getPosition(window).x && squares[i]->getPosition().x + 30 > Mouse::getPosition(window).x && squares[i]->getPosition().y < Mouse::getPosition(window).y && squares[i]->getPosition().y + 30 > Mouse::getPosition(window).y)
					{
						if (squares[i]->getPosition().x == square_x && squares[i]->getPosition().y == square_y && handled_square)
						{
							break;
						}
						square_x = squares[i]->getPosition().x;
						square_y = squares[i]->getPosition().y;
						handled_square = true;
						Cheese.setPosition(squares[i]->getPosition().x, squares[i]->getPosition().y);
						draw_cheese = true;
						endCoord->X = squares[i]->getPosition().x / 30;
						endCoord->Y = squares[i]->getPosition().y / 30;
					}

					a++;
					if (a == x)
					{
						b++;
						a = 0;
					}
				}
			}
			else if (Mouse::isButtonPressed(Mouse::Button::Right))
			{
				int a = 0;
				int b = 0;
				for (int i = 0; i < squares.size(); i++)
				{
					if (squares[i]->getPosition().x < Mouse::getPosition(window).x && squares[i]->getPosition().x + 30 > Mouse::getPosition(window).x && squares[i]->getPosition().y < Mouse::getPosition(window).y && squares[i]->getPosition().y + 30 > Mouse::getPosition(window).y)
					{
						if (squares[i]->getPosition().x == square_x && squares[i]->getPosition().y == square_y && handled_square)
						{
							break;
						}
						square_x = squares[i]->getPosition().x;
						square_y = squares[i]->getPosition().y;
						handled_square = true;
						Mouse.setPosition(squares[i]->getPosition().x, squares[i]->getPosition().y);
						draw_mouse = true;
						startCoord->X = squares[i]->getPosition().x / 30;
						startCoord->Y = squares[i]->getPosition().y / 30;
					}
					a++;
					if (a == x)
					{
						b++;
						a = 0;
					}
				}
			}
			else
			{
				handled_square = false;
			}
		}
		for (int i = 0; i < squares.size(); i++)
		{
			window.draw(*squares[i]);
		}
		if (draw_cheese)
		{
			window.draw(Cheese);
		}
		if (draw_mouse)
		{
			window.draw(Mouse);
		}
		window.display();
	}
	std::ofstream file("NEW_MAZE.maze", std::ios::out | std::ios::binary);
	file.seekp(std::ios::beg);
	file.write((char *)&(x), sizeof(x));
	file.seekp(0, std::ios::end);
	file.write((char *)&(y), sizeof(y));
	file.seekp(0, std::ios::end);
	file.write((char *)startCoord, sizeof(startCoord));
	file.seekp(0, std::ios::end);
	file.write((char *)endCoord, sizeof(endCoord));
	for (int i = 0; i < y; i++)
	{
		for (int z = 0; z < x; z++)
		{
			file.seekp(0, std::ios::end);
			file.write((char *)&(*maze)[i][z], sizeof((*maze)[i][z]));
		}
	}
	file.close();

	for (int i = 0; i < squares.size(); i++)
	{
		delete squares[i];
	}

	delete maze;
	delete startCoord;
	delete endCoord;

	return 0;
}