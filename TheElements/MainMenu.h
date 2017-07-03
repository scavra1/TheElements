#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
class MainMenu
{
public:

	MainMenu(sf::Vector2u windowSize);

	void OnUpdate(sf::Vector2i mousePosition, float wavePhase);

	void OnDraw(sf::RenderWindow& window);

	int GetCurrentOption();
private:

	int currentOption;

	sf::Font menuFont;

	sf::Shader menuShader;

	std::vector<sf::Text> options;
};