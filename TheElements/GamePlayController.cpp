#include "GamePlayController.h"
#include <iostream>

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

	this->playerOneHealth->SetPosition(sf::Vector2f(20, 20));
	this->playerOneMana->SetPosition(sf::Vector2f(20, 45));
	
	this->playerTwoHealth->SetPosition(sf::Vector2f(1110, 20));
	this->playerTwoMana->SetPosition(sf::Vector2f(1110, 45));

	this->playerOneSpellBar = new SpellBar();
	this->playerTwoSpellBar = new SpellBar();

	this->playerOneSpellBar->SetElementPosition(sf::Vector2f(25, 70), Elements::Fire);
	this->playerOneSpellBar->SetElementPosition(sf::Vector2f(60, 70), Elements::Water);
	this->playerOneSpellBar->SetElementPosition(sf::Vector2f(95, 70), Elements::Shadow);
	this->playerOneSpellBar->SetElementPosition(sf::Vector2f(130, 70), Elements::Earth);

	this->playerTwoSpellBar->SetElementPosition(sf::Vector2f(1115, 70), Elements::Fire);
	this->playerTwoSpellBar->SetElementPosition(sf::Vector2f(1150, 70), Elements::Water);
	this->playerTwoSpellBar->SetElementPosition(sf::Vector2f(1185, 70), Elements::Shadow);
	this->playerTwoSpellBar->SetElementPosition(sf::Vector2f(1220, 70), Elements::Earth);

	this->blocks.push_back(Block(400, 200, 100, 200));
	this->blocks.push_back(Block(600, 500, 200, 100));

	this->window = window;

	this->gameSceneTexture.create(1280, 720, false);
	this->gameSceneSprite.setTexture(gameSceneTexture.getTexture());

	if (!this->pauseShader.loadFromFile("shaders/wb.frag", sf::Shader::Type::Fragment))
		throw std::string("Could not load shader in objects loader");
}

void GamePlayController::UpdateGamePlay()
{
	if (!this->isGamePaused)
	{
		//Regenerate mana
		this->playerOne->IncreaseMana(1);
		this->playerTwo->IncreaseMana(1);
		this->playerOneMana->AddResource(1);
		this->playerTwoMana->AddResource(1);

		this->playerOneHealth->OnUpdate();
		this->playerOneMana->OnUpdate();

		this->playerTwoHealth->OnUpdate();
		this->playerTwoMana->OnUpdate();

		this->playerOne->OnUpdate();
		this->playerTwo->OnUpdate();

		this->handleSteering();
		this->handleParticles();

		//Shooting
		if (this->window->hasFocus())
		{
			double manaNeeded = 3.0;	//3.0
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				for (int i = 0; i < 1; i++)
				{
					if (this->playerOne->UseMana(manaNeeded)) {
						this->playerOneParticles.push_back(this->playerOne->generateParticle(Elements::Fire));
						this->playerOneMana->SubtractResource(manaNeeded);
					}

				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
				for (int i = 0; i < 1; i++)
				{

					if (this->playerTwo->UseMana(manaNeeded * 1)) {
						this->playerTwoParticles.push_back(this->playerTwo->generateParticle(Elements::Fire));
						this->playerTwoMana->SubtractResource(manaNeeded * 1);
					}
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) this->playerOneSpellBar->UseSpell(Elements::Fire);
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
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::P)
				this->isGamePaused = !this->isGamePaused;
			break;
		}
	}
}

void GamePlayController::handleSteering()
{
	const double straightSpeed = 4.0;
	const double sidewaysSpeed = 3.0;
	const double rotateSpeed = 0.04;

	double straightDistance1 = 0.0;
	double sidewaysDistance1 = 0.0;
	double rotation1 = 0.0;
	double straightDistance2 = 0.0;
	double sidewaysDistance2 = 0.0;
	double rotation2 = 0.0;

	if (this->window->hasFocus())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) straightDistance1 += straightSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) straightDistance1 -= straightSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotation1 -= rotateSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotation1 += rotateSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) sidewaysDistance1 -= sidewaysSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) sidewaysDistance1 += sidewaysSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) straightDistance2 += straightSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) straightDistance2 -= straightSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) rotation2 -= rotateSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) rotation2 += rotateSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) sidewaysDistance2 -= sidewaysSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) sidewaysDistance2 += sidewaysSpeed;
	}

	playerOne->MoveForward(straightDistance1);
	playerOne->MoveRight(sidewaysDistance1);
	playerOne->RotateRight(rotation1);
	playerTwo->MoveForward(straightDistance2);
	playerTwo->MoveRight(sidewaysDistance2);
	playerTwo->RotateRight(rotation2);

	this->handlePlayersCollisions(straightDistance1, sidewaysDistance1, rotation1, straightDistance2, sidewaysDistance2, rotation2);
}

void GamePlayController::handlePlayersCollisions(double straightDistance1, double sidewaysDistance1, double rotation1, double straightDistance2, double sidewaysDistance2, double rotation2)
{
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

void GamePlayController::handleParticles()
{
	//Removing dead particles
	for (int i = 0; i < this->playerOneParticles.size(); i++) {
		if (!this->playerOneParticles[i].isAlive())
		{
			this->playerOneParticles.erase(this->playerOneParticles.begin() + i);
		}
	}
	for (int i = 0; i < this->playerTwoParticles.size(); i++) {
		if (!this->playerTwoParticles[i].isAlive())
		{
			this->playerTwoParticles.erase(this->playerTwoParticles.begin() + i);
		}
	}

	//PlayerOneParticles collisions with blocks and players
	for (int i = 0; i < this->playerOneParticles.size(); i++) {
		this->playerOneParticles[i].OnUpdate(1.0);
		if (this->playerOneParticles[i].getType() == Elements::Water) {
			double playerX = this->playerOne->getX();
			double playerY = this->playerOne->getY();
			this->playerOneParticles[i].move(playerX - this->playerOne->getLastX(), playerY - this->playerOne->getLastY());
			double x = this->playerOneParticles[i].getX();
			double y = this->playerOneParticles[i].getY();
			double vx = this->playerOneParticles[i].getVx();
			double vy = this->playerOneParticles[i].getVy();
			double dx = playerX - x;
			double dy = playerY - y;
			double distance = hypot(dx, dy);

			if (distance < 100) {
				double force = 5e3 / distance / distance;
				double dvx = force * dx / distance;
				double dvy = force * dy / distance;
				this->playerOneParticles[i].setSpeed(vx + dvx, vy + dvy);
			}
		}
		else {
			for (int j = 0; j < this->blocks.size(); j++) {
				if (this->blocks[j].containsPoint(this->playerOneParticles[i].getX(), this->playerOneParticles[i].getY()))
				{
					bool vertical = this->blocks[j].isIntersectingVerticalWall(
						this->playerOneParticles[i].getX(),
						this->playerOneParticles[i].getY(),
						this->playerOneParticles[i].getLastX(),
						this->playerOneParticles[i].getLastY()
					);
					if (vertical) {
						this->playerOneParticles[i].setSpeed(-this->playerOneParticles[i].getVx(), this->playerOneParticles[i].getVy());
					}
					else {
						this->playerOneParticles[i].setSpeed(this->playerOneParticles[i].getVx(), -this->playerOneParticles[i].getVy());
					}
				}
			}
			if (this->playerTwo->checkCollision(this->playerOneParticles[i].getX(), this->playerOneParticles[i].getY())) {
				this->playerOneParticles[i].kill();
				this->playerTwo->TakeDamage(2.0);
				this->playerTwoHealth->SubtractResource(2.0);
			}
		}
	}

	//PlayerTwoParticles collisions with blocks and players
	for (int i = 0; i < this->playerTwoParticles.size(); i++) {
		this->playerTwoParticles[i].OnUpdate(1.0);
		if (this->playerTwoParticles[i].getType() == Elements::Water) {
			double playerX = this->playerTwo->getX();
			double playerY = this->playerTwo->getY();
			this->playerTwoParticles[i].move(playerX - this->playerTwo->getLastX(), playerY - this->playerTwo->getLastY());
			double x = this->playerTwoParticles[i].getX();
			double y = this->playerTwoParticles[i].getY();
			double vx = this->playerTwoParticles[i].getVx();
			double vy = this->playerTwoParticles[i].getVy();
			double dx = playerX - x;
			double dy = playerY - y;
			double distance = hypot(dx, dy);

			if (distance < 100) {
				double force = 5e3 / distance / distance;
				double dvx = force * dx / distance;
				double dvy = force * dy / distance;
				this->playerTwoParticles[i].setSpeed(vx + dvx, vy + dvy);
			}
		}
		else {
			for (int j = 0; j < this->blocks.size(); j++) {
				if (this->blocks[j].containsPoint(this->playerTwoParticles[i].getX(), this->playerTwoParticles[i].getY()))
				{
					bool vertical = this->blocks[j].isIntersectingVerticalWall(
						this->playerTwoParticles[i].getX(),
						this->playerTwoParticles[i].getY(),
						this->playerTwoParticles[i].getLastX(),
						this->playerTwoParticles[i].getLastY()
					);
					if (vertical) {
						this->playerTwoParticles[i].setSpeed(-this->playerTwoParticles[i].getVx(), this->playerTwoParticles[i].getVy());
					}
					else {
						this->playerTwoParticles[i].setSpeed(this->playerTwoParticles[i].getVx(), -this->playerTwoParticles[i].getVy());
					}
				}
			}
			if (this->playerOne->checkCollision(this->playerTwoParticles[i].getX(), this->playerTwoParticles[i].getY())) {
				this->playerTwoParticles[i].kill();
				this->playerOne->TakeDamage(2.0);
				this->playerOneHealth->SubtractResource(2.0);
			}
		}
	}

	//particle - particle collisions
	const double maxDistance = 22.0;
	for (int i = 0; i < this->playerOneParticles.size(); i++) {
		double x1 = this->playerOneParticles[i].getX();
		double y1 = this->playerOneParticles[i].getY();
		bool killedParticlesFlag = false;
		for (int j = 0; j < this->playerTwoParticles.size(); j++) {
			if (!(this->playerOneParticles[i].getType() == this->playerTwoParticles[j].getType() && this->playerTwoParticles[j].getType() == Elements::Water)) {
				double x2 = this->playerTwoParticles[j].getX();
				double y2 = this->playerTwoParticles[j].getY();
				double distance = hypot(x1 - x2, y1 - y2);
				if (distance < maxDistance) {
					if (this->playerOneParticles[i].getType() != this->playerTwoParticles[j].getType()) {
						this->playerOneParticles[i].kill();
						this->playerTwoParticles[j].kill();
						killedParticlesFlag = true;
						break;
					}
					else {
						double vx1 = this->playerOneParticles[i].getVx();
						double vy1 = this->playerOneParticles[i].getVy();
						double vx2 = this->playerTwoParticles[j].getVx();
						double vy2 = this->playerTwoParticles[j].getVy();

						double k2 = distance / maxDistance;
						double k1 = 1.0 - k2;

						this->playerOneParticles[i].setSpeed(vx1 * k2 + vx2 * k1, vy1 * k2 + vy2 * k1);
						this->playerTwoParticles[j].setSpeed(vx1 * k1 + vx2 * k2, vy1 * k1 + vy2 * k2);
					}
				}
			}
		}
		if (killedParticlesFlag) {
			break;
		}
	}
}

void GamePlayController::DrawGamePlay()
{
	if (!this->isGamePaused)
	{
		for (auto particle : this->playerOneParticles) {
			particle.OnDraw(*this->window);
		}
		for (auto particle : this->playerTwoParticles) {
			particle.OnDraw(*this->window);
		}

		this->playerOne->OnDraw(*this->window);
		this->playerTwo->OnDraw(*this->window);

		for (Block block : this->blocks) {
			block.OnDraw(*this->window);
		}

		this->playerOneHealth->OnDraw(*this->window);
		this->playerOneMana->OnDraw(*this->window);

		this->playerTwoHealth->OnDraw(*this->window);
		this->playerTwoMana->OnDraw(*this->window);

		this->playerOneSpellBar->OnDraw(*this->window);
		this->playerTwoSpellBar->OnDraw(*this->window);
	}
	else
	{
		this->pauseShader.setUniform("pause", true);

		this->gameSceneTexture.clear(sf::Color::White);

		for (auto particle : this->playerOneParticles) {
			particle.OnDraw(this->gameSceneTexture);
		}
		for (auto particle : this->playerTwoParticles) {
			particle.OnDraw(this->gameSceneTexture);
		}

		this->playerOne->OnDraw(this->gameSceneTexture);
		this->playerTwo->OnDraw(this->gameSceneTexture);

		for (Block block : this->blocks) {
			block.OnDraw(this->gameSceneTexture);
		}

		this->playerOneHealth->OnDraw(this->gameSceneTexture);
		this->playerOneMana->OnDraw(this->gameSceneTexture);

		this->playerTwoHealth->OnDraw(this->gameSceneTexture);
		this->playerTwoMana->OnDraw(this->gameSceneTexture);

		this->playerOneSpellBar->OnDraw(this->gameSceneTexture);
		this->playerTwoSpellBar->OnDraw(this->gameSceneTexture);

		this->gameSceneTexture.display();

		this->window->draw(gameSceneSprite, &this->pauseShader);
	}
}
