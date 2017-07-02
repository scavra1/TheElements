#include "GamePlayController.h"

GamePlayController::GamePlayController(sf::RenderWindow * window)
{
	playerOne = new Wizard(200, 400);
	playerTwo = new Wizard(200, 400);

	playerOneHealth = new ResourceBar(200, 200);
	playerTwoHealth = new ResourceBar(200, 200);

	playerOneMana = new ManaBar(400, 400);
	playerTwoMana = new ManaBar(400, 400);

	playerOneHealth->SetPosition(sf::Vector2f(0, 20));
	playerOneMana->SetPosition(sf::Vector2f(0, 50));

	playerTwoHealth->SetPosition(sf::Vector2f(1000, 20));
	playerTwoMana->SetPosition(sf::Vector2f(1000, 50));

	this->window = window;
}

void GamePlayController::UpdateGamePlay()
{
	this->playerOneHealth->OnUpdate();
	this->playerOneMana->OnUpdate();

	this->playerTwoHealth->OnUpdate();
	this->playerTwoMana->OnUpdate();
}

void GamePlayController::PollGamePlayEvents()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void GamePlayController::DrawGamePlay()
{
	this->playerOneHealth->OnDraw(*this->window);
	this->playerOneMana->OnDraw(*this->window);

	this->playerTwoHealth->OnDraw(*this->window);
	this->playerTwoMana->OnDraw(*this->window);
}
