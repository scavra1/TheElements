#include "Block.h"
#include <math.h>


/**
* Constructor. Sets block's position and dimensions
*/
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

/**
* Method that is responsible for drawing block on the screen
*/
void Block::OnDraw(sf::RenderTarget & window)
{
	sf::RectangleShape rectangle(sf::Vector2f(this->width, this->height));
	rectangle.setPosition(this->x - this->width / 2, this->y - this->height / 2);
	rectangle.setFillColor(sf::Color(255, 128, 0));
	window.draw(rectangle);
}

/**
* Checks if block contains given point
*/
bool Block::containsPoint(double pointX, double pointY)
{
	return	pointX > this->x - this->width / 2 &&
			pointX < this->x + this->width / 2 &&
			pointY > this->y - this->height / 2 &&
			pointY < this->y + this->height / 2;
}

/**
* Checks if segment (given by two points) is intersecting block's vertical wall
*/
bool Block::isIntersectingVerticalWall(double p1x, double p1y, double p2x, double p2y)
{
	double a = (p2y - p1y) / (p2x - p1x);
	double y1 = p1y + ((this->x - this->width / 2) - p1x) * a;
	double y2 = p1y + ((this->x + this->width / 2) - p1x) * a;
	return	(y1 >= this->y - this->height / 2 && y1 <= this->y + this->height / 2 && y1 > std::min(p1y, p2y) && y1 < std::max(p1y, p2y)) ||
			(y2 >= this->y - this->height / 2 && y2 <= this->y + this->height / 2 && y2 > std::min(p1y, p2y) && y2 < std::max(p1y, p2y));
}
