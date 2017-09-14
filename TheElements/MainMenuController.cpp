#include "MainMenuController.h"

/**
* Constructor. Aggregates menu object with render target.
* @param window render target
* @param mainMenu menu object
*/
MainMenuController::MainMenuController(sf::RenderWindow* window, MainMenu* mainMenu)
{
	this->window = window;
	this->mainMenu = mainMenu;
}

/**
* Polls window events and reflects the change with returned menu state.
*/
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

/**
* Fires update of the scene when game is in mainmenu state.
* @param mousePosition mouse coordinates
* @param wavePhase floating shader parameter
*/
void MainMenuController::UpdateMainMenu(sf::Vector2i& mousePosition, float wavePhase)
{
	this->mainMenu->OnUpdate(mousePosition, wavePhase);
}

/**
* Draws the scene when game is in mainmenu state.
*/
void MainMenuController::DrawMainMenu()
{
	this->mainMenu->OnDraw(*this->window);
}
