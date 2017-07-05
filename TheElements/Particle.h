#pragma once
#include <SFML\Graphics.hpp>
class Particle
{
public:
	Particle(double x, double y, double vx, double vy);
	void OnUpdate(double dt);
	void OnDraw(sf::RenderTarget & window);
	bool isAlive();
	void kill();
	double getX() { return this->x; };
	double getY() { return this->y; };
private:
	double x;
	double y;
	double vx;
	double vy;
	double age = 0;
	double lifeTime;
};