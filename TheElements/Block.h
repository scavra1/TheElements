#pragma once
#include <SFML\Graphics.hpp>
class Block
{
public:
	Block(double x, double y, double width, double height);
	~Block();
	void OnDraw(sf::RenderTarget & window);
	bool containsPoint(double pointX, double pointY);
	bool isIntersectingVerticalWall(double p1x, double p1y, double p2x, double p2y);
private:
	double x;
	double y;
	double width;
	double height;
};

