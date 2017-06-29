#include "ManaBar.h"

ManaBar::ManaBar(int startLoad, int maxCapacity)
{
	this->load = startLoad;
	this->maximumCapacity = maxCapacity;

	if (!this->shader.loadFromFile("shaders/manaBar.frag", sf::Shader::Type::Fragment))
		throw std::string("Could not load shader in mana bar loader.");

	if (!this->texture.loadFromFile("textures/bar.png"))
		throw std::string("Could not load texture in mana bar loader.");
}

void ManaBar::AddResource(int value)
{
	if ((this->load += value) > this->maximumCapacity)
	{
		this->load = this->maximumCapacity;
	}
}

void ManaBar::SubtractResource(int value)
{
	if ((this->load -= value) < 0)
	{
		this->load = 0;
	}
}

void ManaBar::SetPosition(sf::Vector2f position)
{
	this->barSprite.setPosition(position);
}

void ManaBar::OnUpdate()
{
}

void ManaBar::OnDraw(sf::RenderWindow & window)
{
	window.draw(this->barSprite, sf::RenderStates(&this->shader));
}
