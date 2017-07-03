#include "GamePlayController.h"

GamePlayController::GamePlayController(sf::RenderWindow * window)
{
	this->playerOne = new Wizard(200, 400);
	this->playerTwo = new Wizard(200, 400);

	this->playerOne->SetPosition(100, 100, 3.14 / 2.0);
	this->playerTwo->SetPosition(900, 500, 0);

	this->playerOneHealth = new ResourceBar(200, 200);
	this->playerTwoHealth = new ResourceBar(200, 200);

	this->playerOneMana = new ManaBar(400, 400);
	this->playerTwoMana = new ManaBar(400, 400);

	this->playerOneHealth->SetPosition(sf::Vector2f(0, 20));
	this->playerOneMana->SetPosition(sf::Vector2f(0, 50));
	
	this->playerTwoHealth->SetPosition(sf::Vector2f(1000, 20));
	this->playerTwoMana->SetPosition(sf::Vector2f(1000, 50));

	this->playerOneSpellBar = new SpellBar();
	this->playerTwoSpellBar = new SpellBar();

	this->playerOneSpellBar->SetElementPosition(sf::Vector2f(0, 400), Elements::Fire);

	this->window = window;
}

void GamePlayController::UpdateGamePlay()
{
	this->playerOneHealth->OnUpdate();
	this->playerOneMana->OnUpdate();

	this->playerTwoHealth->OnUpdate();
	this->playerTwoMana->OnUpdate();

	this->playerOne->OnUpdate();
	this->playerTwo->OnUpdate();

	const double straightSpeed = 4.0;
	const double sidewaysSpeed = 3.0;
	const double rotateSpeed = 0.03;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->playerOne->MoveForward(straightSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->playerOne->MoveBackward(straightSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->playerOne->MoveLeft(sidewaysSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->playerOne->MoveRight(sidewaysSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) this->playerOne->RotateLeft(rotateSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) this->playerOne->RotateRight(rotateSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) this->playerTwo->MoveForward(straightSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) this->playerTwo->MoveBackward(straightSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) this->playerTwo->MoveLeft(sidewaysSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) this->playerTwo->MoveRight(sidewaysSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) this->playerTwo->RotateLeft(rotateSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) this->playerTwo->RotateRight(rotateSpeed);
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

	this->playerOne->OnDraw(*this->window);
	this->playerTwo->OnDraw(*this->window);

	this->playerOneSpellBar->OnDraw(*this->window);
}
