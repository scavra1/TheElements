#include "MainMenuController.h"


MainMenuController::MainMenuController(sf::RenderWindow* window, MainMenu* mainMenu)
{
	this->window = window;
	this->mainMenu = mainMenu;
}

MainMenuStates MainMenuController::PollMainMenuEvents()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				int optionPicked = this->mainMenu->GetCurrentOption();
				if (optionPicked > -1)
				{
					return (MainMenuStates)optionPicked;
				}
			}
			break;
		case sf::Event::Closed:
			return MainMenuStates::Exit;
		}
	}
	return MainMenuStates::None;
}

void MainMenuController::UpdateMainMenu(sf::Vector2i& mousePosition, float wavePhase)
{
	this->mainMenu->OnUpdate(mousePosition, wavePhase);
}

void MainMenuController::DrawMainMenu()
{
	this->mainMenu->OnDraw(*this->window);
}
