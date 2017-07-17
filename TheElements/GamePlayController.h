#pragma once
#include "ManaBar.h"
#include "ResourceBar.h"
#include "Wizard.h"
#include "Block.h"
#include <vector>
#include "SpellBar.h"
#include "Particle.h"

class GamePlayController
{
public: 

	GamePlayController(sf::RenderWindow* window);

	 void UpdateGamePlay();

	 void PollGamePlayEvents();

	 void DrawGamePlay();


private:

	sf::RenderWindow* window;

	Wizard* playerOne;

	Wizard* playerTwo;

	ResourceBar* playerOneHealth;

	ResourceBar* playerTwoHealth;

	ManaBar* playerOneMana;

	ManaBar* playerTwoMana;

	std::vector<Block> blocks;

	SpellBar* playerOneSpellBar;

	SpellBar* playerTwoSpellBar;

	std::vector<Particle> playerOneParticles;

	std::vector<Particle> playerTwoParticles;

	void handleSteering();

	void handlePlayersCollisions(double straightDistance1, double sidewaysDistance1, double rotation1, double straightDistance2, double sidewaysDistance2, double rotation2);

	void handleParticles();

};