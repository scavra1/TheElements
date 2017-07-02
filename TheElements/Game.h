#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "Wizard.h";
namespace GameSpace
{
	class Game
	{
	public:
		Game();
		~Game();
		void OnUpdate(double dt);
		void OnDraw(sf::RenderWindow & window);
		void AddWizard(Wizard* wizard);
	private:
		std::vector<Wizard*> wizards;
	};
}