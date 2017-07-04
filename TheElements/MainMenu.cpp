#include "MainMenu.h"

MainMenu::MainMenu(sf::Vector2u windowSize)
{
	if (!this->menuFont.loadFromFile("fonts/sansation.ttf"))
		throw std::string("Could not load font in menu loader.");

	sf::Text newGame("New Game", this->menuFont, 70);
	sf::Text settings("Settings", this->menuFont, 70);
	sf::Text authors("Authors", this->menuFont, 70);
	sf::Text credits("Credits", this->menuFont, 70);
	sf::Text exit("Exit", this->menuFont, 70);

	newGame.setFillColor(sf::Color::Red);
	newGame.setPosition((windowSize.x - newGame.getLocalBounds().width) / 2, 50);

	settings.setFillColor(sf::Color::Red);
	settings.setPosition((windowSize.x - settings.getLocalBounds().width) / 2, 150);

	authors.setFillColor(sf::Color::Red);
	authors.setPosition((windowSize.x - authors.getLocalBounds().width) / 2, 250);

	credits.setFillColor(sf::Color::Red);
	credits.setPosition((windowSize.x - credits.getLocalBounds().width) / 2, 350);

	exit.setFillColor(sf::Color::Red);
	exit.setPosition((windowSize.x - exit.getLocalBounds().width) / 2, 450);

	options.push_back(newGame);
	options.push_back(settings);
	options.push_back(authors);
	options.push_back(credits);
	options.push_back(exit);

	if (!this->menuShader.loadFromFile("shaders/wave.vert", "shaders/blur.frag"))
		throw std::string("Could not load shaders in menu loader.");

	this->currentOption = -1;
}

void MainMenu::OnUpdate(sf::Vector2i mousePosition, float wavePhase)
{
	currentOption = -1;
	for (int i = 0; i < this->options.size(); i++)
	{
		if (this->options[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			this->currentOption = i;
		}
	}

	this->menuShader.setUniform("wave_phase", wavePhase);
	this->menuShader.setUniform("wave_amplitude", sf::Vector2f(5, 5));
	this->menuShader.setUniform("blur_radius", 0.0f);
}

void MainMenu::OnDraw(sf::RenderWindow & window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	for (size_t i = 0; i < this->options.size(); i++)
	{
		if (i == this->currentOption)
		{
			window.draw(this->options[i], &this->menuShader);
		}
		else
		{
			window.draw(this->options[i]);
		}
	}
}

int MainMenu::GetCurrentOption()
{
	return this->currentOption;
}



