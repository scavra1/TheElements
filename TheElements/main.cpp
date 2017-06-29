#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "MainMenu.h"
#include "ResourceBar.h"

int main(int argc, char ** argv)
{
	const int WindowSizeX = 1280;
	const int WindowSizeY = 720;

	sf::RenderWindow window(sf::VideoMode(WindowSizeX, WindowSizeY, 32), "SFML works!");
	window.setVerticalSyncEnabled(true);

	MainMenu mainMenu(sf::Vector2u(WindowSizeX, WindowSizeY));
	
	ResourceBar hpBar(50, 200);

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					hpBar.AddResource(20);
				}
				else
				{
					hpBar.SubtractResource(20);
				}
			}
		}

		mainMenu.OnUpdate(std::cos(clock.getElapsedTime().asSeconds()));
		hpBar.OnUpdate();
		
		window.clear(sf::Color::White);

		mainMenu.OnDraw(window);
		hpBar.OnDraw(window);

		window.display();
	}

	return 0;
}

