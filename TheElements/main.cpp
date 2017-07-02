#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "MainMenu.h"
#include "ResourceBar.h"
#include "ManaBar.h"
#include "MainMenuStates.h"
#include "MainMenuController.h"
#include "GamePlayController.h"
#include <iostream>

int main(int argc, char ** argv)
{
	const int WindowSizeX = 1280;
	const int WindowSizeY = 720;

	sf::RenderWindow window(sf::VideoMode(WindowSizeX, WindowSizeY, 32), "SFML works!");
	window.setVerticalSyncEnabled(true);

	MainMenu mainMenu(sf::Vector2u(WindowSizeX, WindowSizeY));
	MainMenuController mainMenuController(&window, &mainMenu);

	//ResourceBar hpBar(50, 200);
	//ManaBar manaBar(400, 1000);

	//manaBar.SetPosition(sf::Vector2f(0, 200));

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
			//hpBar.OnUpdate();
			//manaBar.OnUpdate();
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


		window.clear(sf::Color::White);


		switch (mainMenuStates)
		{
		case MainMenuStates::None:
			mainMenuController.DrawMainMenu();
			//update scene in menu
			break;
		case MainMenuStates::Game:
			gamePlayController.DrawGamePlay();
//			hpBar.OnDraw(window);
			//manaBar.OnDraw(window);
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




		window.display();
	}

	return 0;
}

