#include "Particle.h"

/**
* Constructor. Sets particle's position, velocity and type
*/
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

/**
* Method that should be called before every frame
*/
void Particle::OnUpdate(double dt)
{
	this->age += dt;
	this->lastX = this->x;
	this->lastY = this->y;
	this->x += this->vx;
	this->y += this->vy;
}

/**
* Method that is responsible for drawing particle on the screen
*/
void Particle::OnDraw(sf::RenderTarget & window)
{
	int radius = 8;
	sf::RectangleShape shape(sf::Vector2f(radius, radius));
	double a = a = 255 / (this->lifeTime * this->lifeTime);
	double waterColor = -this->age*this->age * a + 255.0;
	double fireColor = 6 * 255 * this->age / this->lifeTime;
	double b = 255 - (fireColor > 255 ? 255 : fireColor);
	double g = 255 - (fireColor - 255 > 255 ? 255 : (fireColor - 255 < 0 ? 0 : fireColor - 255));
	switch (this->type) {
	case Elements::Fire:
		
		shape.setFillColor(sf::Color(255, g, b));
		//shape.setFillColor(sf::Color(255, 255 - color, 255 - color));
		break;
	case Elements::Water:
		shape.setFillColor(sf::Color(255 - waterColor, 255 - waterColor, 255));
		break;
	case Elements::Earth:
		shape.setFillColor(sf::Color(255 - waterColor, 255, 255 - waterColor));
		break;
	case Elements::Shadow:
		shape.setFillColor(sf::Color(255 - waterColor, 255 - waterColor, 255 - waterColor));
		break;
	}
	shape.setPosition(this->x- radius/2, this->y- radius / 2);
	shape.setRotation(45);
	window.draw(shape);
}

/**
* Applies force on particle
* @param fx force in x axis.
* @param fy force in y axis.
*/
void Particle::applyForce(double fx, double fy)
{
	this->vx += fx;
	this->vy += fy;
}

/**
* Returns true if particle's age is lesser than its lifetime. False otherwise.
*/
bool Particle::isAlive()
{
	return this->age < this->lifeTime;
}

/**
* Sets particle's age to value greater than its lifetime
*/
void Particle::kill()
{
	this->age = this->lifeTime + 1.0;
}
