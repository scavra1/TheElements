#include "ManaBar.h"

ManaBar::ManaBar(int startLoad, int maxCapacity)
{
	this->load = startLoad;
	this->maximumCapacity = maxCapacity;

	if (!this->shader.loadFromFile("shaders/manaBar.frag", sf::Shader::Type::Fragment))
		throw std::string("Could not load shader in mana bar loader.");

	if (!this->texture.loadFromFile("textures/bar.png"))
		throw std::string("Could not load texture in mana bar loader.");

	this->barSprite.setTexture(texture);
	this->shader.setUniform("barSize", (int)this->texture.getSize().x);
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
	this->shader.setUniform("loadRatio", ((float)this->load / this->maximumCapacity));
	this->shader.setUniform("beginPosition", (float)this->barSprite.getPosition().x);
}

void ManaBar::OnDraw(sf::RenderTarget & window)
{
	window.draw(this->barSprite, sf::RenderStates(&this->shader));
}
