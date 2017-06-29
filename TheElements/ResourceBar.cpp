#include "ResourceBar.h"

ResourceBar::ResourceBar(int startLoad, int maxCapacity)
{
	this->load = startLoad;
	this->maximumCapacity = maxCapacity;

	if (!this->shader.loadFromFile("shaders/hpBar.frag", sf::Shader::Type::Fragment))
		throw std::string("Could not load fragment shader in resource bar loader.");

	if (!this->texture.loadFromFile("textures/bar.png"))
		throw std::string("Could not load texture in resource bar loader.");

	this->barSprite.setTexture(this->texture);
	this->shader.setUniform("barSize", (int)this->texture.getSize().x);
}

void ResourceBar::AddResource(int value)
{
	if ((this->load += value) > this->maximumCapacity)
	{
		this->load = this->maximumCapacity;
	}
}

void ResourceBar::SubtractResource(int value)
{
	if ((this->load -= value) < 0)
	{
		this->load = 0;
	}
}

void ResourceBar::SetPosition(sf::Vector2f position)
{
	this->barSprite.setPosition(position);
}

void ResourceBar::OnUpdate()
{
	this->shader.setUniform("loadRatio", ((float)this->load / this->maximumCapacity));
}

void ResourceBar::OnDraw(sf::RenderWindow & window)
{
	window.draw(this->barSprite, sf::RenderStates(&this->shader));
}
