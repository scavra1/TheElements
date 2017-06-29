#include "MainMenu.h"

MainMenu::MainMenu(sf::Vector2u windowSize)
{
	if (!this->menuFont.loadFromFile("fonts/sansation.ttf"))
		throw std::string("Could not load font in menu loader.");

	sf::Text newGame("New Game", this->menuFont, 70);
	sf::Text authors("Authors", this->menuFont, 70);
	sf::Text exit("Exit", this->menuFont, 70);

	newGame.setFillColor(sf::Color::Red);
	newGame.setPosition((windowSize.x - newGame.getLocalBounds().width) / 2, 50);

	authors.setFillColor(sf::Color::Red);
	authors.setPosition((windowSize.x - authors.getLocalBounds().width) / 2, 150);

	exit.setFillColor(sf::Color::Red);
	exit.setPosition((windowSize.x - exit.getLocalBounds().width) / 2, 250);

	options.push_back(newGame);
	options.push_back(authors);
	options.push_back(exit);

	if (!this->menuShader.loadFromFile("shaders/wave.vert", "shaders/blur.frag"))
		throw std::string("Could not load shaders in menu loader.");
}

void MainMenu::OnUpdate(float wavePhase)
{
	this->menuShader.setUniform("wave_phase", wavePhase);
	this->menuShader.setUniform("wave_amplitude", sf::Vector2f(5, 5));
	this->menuShader.setUniform("blur_radius", 0.0f);
}

void MainMenu::OnDraw(sf::RenderWindow & window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	for each (sf::Text option in options)
	{
		if (option.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			window.draw(option, &this->menuShader);
		}
		else
		{
			window.draw(option);
		}
	}
}



