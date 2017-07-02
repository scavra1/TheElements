#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "MainMenu.h"
#include "ResourceBar.h"
#include "ManaBar.h"
#include "Game.h"
#include "MainMenuStates.h"
#include "Wizard.h"

int main(int argc, char ** argv)
{
	const int WindowSizeX = 1280;
	const int WindowSizeY = 720;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 5;
	sf::RenderWindow window(sf::VideoMode(WindowSizeX, WindowSizeY, 32), "SFML works!", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	MainMenu mainMenu(sf::Vector2u(WindowSizeX, WindowSizeY));
	
	ResourceBar hpBar(50, 200);
	ManaBar manaBar(400, 1000);

	manaBar.SetPosition(sf::Vector2f(0, 200));

	GameSpace::Game game;
	Wizard player1(100, 100);
	player1.SetPosition(600, 400, 3.141 / 8.0);
	game.AddWizard(&player1);


	sf::Clock clock;
	MainMenuStates mainMenuStates = MainMenuStates::Game;
	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			switch (mainMenuStates)
			{
				case MainMenuStates::None:
					// poll Events in menu
					break;
				case MainMenuStates::Game:
					// poll events in gameplay
					break;
				case MainMenuStates::Settings:
					// poll events in setting section
					break;
				case MainMenuStates::Exit:
					// poll events while exiting the game
					break;
				default:
					throw "Not supported exception.";
			}
			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					hpBar.AddResource(20);
					manaBar.AddResource(30);
				}
				else
				{
					hpBar.SubtractResource(20);
					manaBar.SubtractResource(30);
				}
			}
		}

		switch (mainMenuStates)
		{
		case MainMenuStates::None:
			//update scene in menu
			break;
		case MainMenuStates::Game:
			// update scene in gameplay
			break;
		case MainMenuStates::Settings:
			// update scene in setting section
			break;
		case MainMenuStates::Exit:
			// update scene while exiting the game
			break;
		default:
			throw "Not supported exception.";
		}

		mainMenu.OnUpdate(mousePosition, std::cos(clock.getElapsedTime().asSeconds()));
		hpBar.OnUpdate();
		manaBar.OnUpdate();
		
		window.clear(sf::Color::White);


		switch (mainMenuStates)
		{
		case MainMenuStates::None:
			//update scene in menu
			mainMenu.OnDraw(window);
			manaBar.OnDraw(window);
			hpBar.OnDraw(window);
			break;
		case MainMenuStates::Game:
			// update scene in gameplay
			hpBar.OnDraw(window);
			manaBar.OnDraw(window);
			game.OnDraw(window);
			break;
		case MainMenuStates::Settings:
			// update scene in setting section
			break;
		case MainMenuStates::Exit:
			// update scene while exiting the game
			break;
		default:
			throw "Not supported exception.";
		}
		window.display();
	}

	return 0;
}

