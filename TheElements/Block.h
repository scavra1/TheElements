#pragma once
#include <SFML\Graphics.hpp>
class Block
{
public:
	Block(double x, double y, double width, double height);
	~Block();
	void OnDraw(sf::RenderWindow & window);
private:
	double x;
	double y;
	double width;
	double height;
};

