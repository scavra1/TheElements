#pragma once
#include <SFML\Graphics.hpp>
#include "MainMenu.h"
#include "MainMenuStates.h"
class MainMenuController
{
public:

	MainMenuController(sf::RenderWindow* window, MainMenu* mainMenu);

	MainMenuStates PollMainMenuEvents();

	void UpdateMainMenu(sf::Vector2i& mousePosition, float wavePhase);

	void DrawMainMenu();

private:

	sf::RenderWindow* window;

	MainMenu* mainMenu;
	

};