#include "GamePlayController.h"
#include <iostream>

GamePlayController::GamePlayController(sf::RenderWindow * window)
{
	playerOne = new Wizard(200, 400);
	playerTwo = new Wizard(200, 400);

	playerOne->SetPosition(100, 100, 3.14 / 2.0);
	playerTwo->SetPosition(900, 500, 0);

	playerOneHealth = new ResourceBar(200, 200);
	playerTwoHealth = new ResourceBar(200, 200);

	playerOneMana = new ManaBar(400, 400);
	playerTwoMana = new ManaBar(400, 400);

	playerOneHealth->SetPosition(sf::Vector2f(0, 20));
	playerOneMana->SetPosition(sf::Vector2f(0, 50));

	playerTwoHealth->SetPosition(sf::Vector2f(1000, 20));
	playerTwoMana->SetPosition(sf::Vector2f(1000, 50));

	this->blocks.push_back(Block(400, 200, 100, 200));
	this->blocks.push_back(Block(600, 500, 200, 100));

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

	double straightDistance1 = 0.0;
	double sidewaysDistance1 = 0.0;
	double rotation1 = 0.0;
	double straightDistance2 = 0.0;
	double sidewaysDistance2 = 0.0;
	double rotation2 = 0.0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) straightDistance1 += straightSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) straightDistance1 -= straightSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) sidewaysDistance1 -= sidewaysSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) sidewaysDistance1 += sidewaysSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) rotation1 -= rotateSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) rotation1 += rotateSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) straightDistance2 += straightSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) straightDistance2 -= straightSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) sidewaysDistance2 -= sidewaysSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) sidewaysDistance2 += sidewaysSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) rotation2 -= rotateSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) rotation2 += rotateSpeed;

	playerOne->MoveForward(straightDistance1);
	playerOne->MoveRight(sidewaysDistance1);
	playerOne->RotateRight(rotation1);
	playerTwo->MoveForward(straightDistance2);
	playerTwo->MoveRight(sidewaysDistance2);
	playerTwo->RotateRight(rotation2);

	//Check collisions
	const double bounceRotation = 0.1;
	for (Block block : this->blocks) {
		if (playerOne->checkCollision(block))
		{
			playerOne->RotateRight(bounceRotation);
			if (playerOne->checkCollision(block)) {
				playerOne->RotateRight(-bounceRotation * 2);
				if (playerOne->checkCollision(block)) {
					playerOne->RotateRight(bounceRotation);
					playerOne->MoveForward(-straightDistance1);
					playerOne->MoveRight(-sidewaysDistance1);
					playerOne->RotateRight(-rotation1);
				}
			}
		}
		if (playerTwo->checkCollision(block))
		{
			playerTwo->RotateRight(bounceRotation);
			if (playerTwo->checkCollision(block)) {
				playerTwo->RotateRight(-bounceRotation * 2);
				if (playerTwo->checkCollision(block)) {
					playerTwo->RotateRight(bounceRotation);
					playerTwo->MoveForward(-straightDistance2);
					playerTwo->MoveRight(-sidewaysDistance2);
					playerTwo->RotateRight(-rotation2);
				}
			}
		}
	}
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
	
	for (Block block : this->blocks) {
		block.OnDraw(*this->window);
	}
}
