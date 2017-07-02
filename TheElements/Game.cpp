#include "Game.h"

using namespace GameSpace;
Game::Game()
{

}

Game::~Game()
{

}

void Game::OnUpdate(double dt)
{

}

void Game::OnDraw(sf::RenderWindow & window)
{
	for (Wizard* wizard : this->wizards) {
		wizard->OnDraw(window);
	}
}

void Game::AddWizard(Wizard * wizard)
{
	this->wizards.push_back(wizard);
}
