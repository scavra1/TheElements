#include "Particle.h"


Particle::Particle(double x, double y, double vx, double vy, Elements type)
{
	this->x = this->lastX = x;
	this->y = this->lastY = y;
	this->vx = vx;
	this->vy = vy;
	this->type = type;
	switch (type) {
	case Elements::Fire:
		this->lifeTime = 80.0;
		break;
	case Elements::Water:
		this->lifeTime = 15*80.0;
		break;
	default:
		this->lifeTime = 80.0;
		break;
	}
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
	switch (this->type) {
	case Elements::Fire:
		shape.setFillColor(sf::Color(255, 255 - color, 255 - color));
		break;
	case Elements::Water:
		shape.setFillColor(sf::Color(255 - color, 255 - color, 255));
		break;
	case Elements::Earth:
		shape.setFillColor(sf::Color(255 - color, 255, 255 - color));
		break;
	case Elements::Shadow:
		shape.setFillColor(sf::Color(255 - color, 255 - color, 255 - color));
		break;
	}
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
