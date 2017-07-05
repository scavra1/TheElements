#include "Particle.h"


Particle::Particle(double x, double y, double vx, double vy)
{
	this->x = this->lastX = x;
	this->y = this->lastY = y;
	this->vx = vx;
	this->vy = vy;
	this->lifeTime = 80.0;
}

void Particle::OnUpdate(double dt)
{
	this->age += dt;
	this->lastX = this->x;
	this->lastY = this->y;
	this->x += this->vx;
	this->y += this->vy;
}

void Particle::OnDraw(sf::RenderTarget & window)
{
	int radius = 8;
	sf::RectangleShape shape(sf::Vector2f(radius, radius));
	double a = a = 255 / (this->lifeTime * this->lifeTime);
	double color = -this->age*this->age * a + 255.0;
	shape.setFillColor(sf::Color(255, 255 - color, 255 - color));
	shape.setPosition(this->x- radius/2, this->y- radius / 2);
	window.draw(shape);
}

void Particle::applyForce(double fx, double fy)
{
	this->vx += fx;
	this->vy += fy;
}

bool Particle::isAlive()
{
	return this->age < this->lifeTime;
}

void Particle::kill()
{
	this->age = this->lifeTime + 1.0;
}
