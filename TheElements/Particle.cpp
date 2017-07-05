#include "Particle.h"


Particle::Particle(double x, double y, double vx, double vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->lifeTime = 80.0;
}

void Particle::OnUpdate(double dt)
{
	this->age += dt;
	this->x += this->vx;
	this->y += this->vy;
}

void Particle::OnDraw(sf::RenderTarget & window)
{
	int radius = 4;
	sf::CircleShape shape(radius);
	/*
	if(this->isAlive())
		shape.setFillColor(sf::Color(0, 255, 0));
	else
		shape.setFillColor(sf::Color(255, 0, 0));
	//*/
	double a = a = 255 / (this->lifeTime * this->lifeTime);
	double color = -this->age*this->age * a + 255.0;
	shape.setFillColor(sf::Color(255, 255 - color, 255 - color));
	shape.setPosition(this->x- radius/2, this->y- radius / 2);
	window.draw(shape);
}

bool Particle::isAlive()
{
	return this->age < this->lifeTime;
}

void Particle::kill()
{
	this->age = this->lifeTime + 1.0;
}
