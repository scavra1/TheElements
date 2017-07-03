#include "Block.h"



Block::Block(double x, double y, double width, double height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


Block::~Block()
{
}

void Block::OnDraw(sf::RenderWindow & window)
{
	sf::RectangleShape rectangle(sf::Vector2f(this->width, this->height));
	rectangle.setPosition(this->x - this->width / 2, this->y - this->height / 2);
	rectangle.setFillColor(sf::Color(100, 250, 50));
	window.draw(rectangle);
}