#pragma once
#include <SFML\Graphics.hpp>
class Particle
{
public:
	Particle(double x, double y, double vx, double vy);
	void OnUpdate(double dt);
	void OnDraw(sf::RenderWindow & window);
	void applyForce(double fx, double fy);
	bool isAlive();
	void kill();
	double getX() { return this->x; };
	double getY() { return this->y; };
	double getVx() { return this->vx; };
	double getVy() { return this->vy; };
	void setSpeed(double vx, double vy) {
		this->vx = vx;
		this->vy = vy;
	};
	double getStrength() { return 1.0 - this->age / this->lifeTime; };
private:
	double x;
	double y;
	double vx;
	double vy;
	double age = 0;
	double lifeTime;
};