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

	bool isGamePaused;

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

	sf::Shader pauseShader;

	sf::Sprite gameSceneSprite;

	sf::RenderTexture gameSceneTexture;

};