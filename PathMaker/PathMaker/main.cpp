#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>

using namespace sf;

int main()
{
	int x;
	int y;
	std::cout << "How many squares in the x direction do you want?" << std::endl;
	std::cin >> x;
	std::cout << "How many squares in the y direction do you want?" << std::endl;
	std::cin >> y;
	std::cout << "Right click to set endpoint. Double left click to set start point." << std::endl;
	std::cout << "Single left click to create maze place" << std::endl;
	std::cout << "Press s to save" << std::endl;
	
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

	Sprite Mouse;
	Sprite Cheese;
	Texture sprite_sheet;
	sprite_sheet.loadFromFile("mouse_and_cheese_sprite.png");

	Mouse.setTexture(sprite_sheet);
	Mouse.setTextureRect(IntRect(0, 8, 75, 42));
	Mouse.setScale(2.0 / 5.0, 3.0 / 5.0);
	Cheese.setTexture(sprite_sheet);
	Cheese.setTextureRect(IntRect(160, 8, 75, 50));
	Cheese.setScale(2.0 / 5.0, 3.0 / 5.0);

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
		std::cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << std::endl;
		window.display();
	}

	return 0;
}