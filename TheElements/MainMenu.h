#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
class MainMenu
{
public:

	MainMenu(sf::Vector2u windowSize);

	void OnUpdate(float wavePhase);

	void OnDraw(sf::RenderWindow& window);

private:

	sf::Font menuFont;

	sf::Shader menuShader;

	std::vector<sf::Text> options;
};