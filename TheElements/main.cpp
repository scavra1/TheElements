#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "MainMenu.h"
#include "ResourceBar.h"
#include "ManaBar.h"
#include "MainMenuStates.h"
#include "MainMenuController.h"
#include "GamePlayController.h"
#include <iostream>

/**
* Main entry point.
*/
int main(int argc, char ** argv)
{
	srand(time(NULL));

	const int WindowSizeX = 1280;
	const int WindowSizeY = 720;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 5;
	sf::RenderWindow window(sf::VideoMode(WindowSizeX, WindowSizeY, 32), "The Elements", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	MainMenu mainMenu(sf::Vector2u(WindowSizeX, WindowSizeY));
	MainMenuController mainMenuController(&window, &mainMenu);

	GamePlayController gamePlayController(&window);

	sf::Clock clock;
	MainMenuStates mainMenuStates = MainMenuStates::None;
	while (window.isOpen())
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		switch (mainMenuStates)
		{
		case MainMenuStates::None:
			mainMenuStates = mainMenuController.PollMainMenuEvents();
			std::cout << mainMenuStates;
			break;
		case MainMenuStates::Game:
			gamePlayController.PollGamePlayEvents();
			// poll events in gameplay
			break;
		case MainMenuStates::Settings:
			// poll events in setting section
			break;
		case MainMenuStates::Exit:
			window.close();
			break;
		default:
			throw "Not supported exception.";
		}

		switch (mainMenuStates)
		{
		case MainMenuStates::None:
			mainMenuController.UpdateMainMenu(mousePosition, std::cos(clock.getElapsedTime().asSeconds()));
			break;
		case MainMenuStates::Game:
			gamePlayController.UpdateGamePlay();
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

		//mainMenu.OnUpdate(mousePosition, std::cos(clock.getElapsedTime().asSeconds()));


		window.clear(sf::Color(50, 50, 50));


		switch (mainMenuStates)
		{
		case MainMenuStates::None:
			mainMenuController.DrawMainMenu();
			break;
		case MainMenuStates::Game:
			gamePlayController.DrawGamePlay();
			//game.OnDraw(window);
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

