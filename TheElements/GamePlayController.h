#pragma once
#include "ManaBar.h"
#include "ResourceBar.h"
#include "Wizard.h"
#include "SpellBar.h"

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

	SpellBar* playerOneSpellBar;

	SpellBar* playerTwoSpellBar;

};