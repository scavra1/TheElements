#pragma once
#include <SFML\Graphics.hpp>
#include "Elements.h"

class Particle
{
public:
	Particle(double x, double y, double vx, double vy, Elements type);
	void OnUpdate(double dt);

	void OnDraw(sf::RenderTarget & window);

	void applyForce(double fx, double fy);
	bool isAlive();
	void kill();
	double getX() { return this->x; };
	double getY() { return this->y; };
	double getLastX() { return this->lastX; };
	double getLastY() { return this->lastY; };
	double getVx() { return this->vx; };
	double getVy() { return this->vy; };
	void setSpeed(double vx, double vy) {
		this->vx = vx;
		this->vy = vy;
	};
	void setPosition(double x, double y) {
		this->x = x;
		this->y = y;
	};
	void move(double dx, double dy) {
		this->x += dx;
		this->y += dy;
	};
	double getStrength() { return 1.0 - this->age / this->lifeTime; };
	Elements getType() { return this->type; };
private:
	double x;
	double y;
	double vx;
	double vy;
	double age = 0;
	double lifeTime;
	double lastX;
	double lastY;
	Elements type;
};