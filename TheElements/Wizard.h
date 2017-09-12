#pragma once
#include "ResourceBar.h"
#include "ManaBar.h"
#include "Block.h"
#include <utility>
#include <vector>
#include "Particle.h"
class Wizard
{

public:
	Wizard(int maxHealth, int maxMana);

	void SetPosition(double x, double y, double r);

	void MoveLeft(double displacement);

	void MoveRight(double displacement);

	void MoveBackward(double displacement);

	void MoveForward(double displacement);

	void StartAttack();

	void StopAttack();

	void RotateLeft(double angle);

	void RotateRight(double angle);

	void OnUpdate();

	void OnDraw(sf::RenderTarget & window);

	void TakeDamage(int damage);

	bool UseMana(double mana);

	void IncreaseMana(double mana);

	bool checkCollision(Block block);

	bool checkCollision(double pointX, double pointY);

	std::vector<std::pair<double, double>> calculateCorners();

	double getHealth();

	double getMana();

	double getX() { return this->xPosition; };

	double getY() { return this->yPosition; };

	double getLastX() { return this->lastXPosition; };

	double getLastY() { return this->lastYPosition; };

	Particle generateParticle(Elements type);

private:
	double xPosition;

	double yPosition;

	double lastXPosition;

	double lastYPosition;

	double rotation;

	double health;

	double mana;

	double maxMana;

	double isMoving = false;

	int walkAnimationTimer = 0;

	sf::Sprite wizardSprite;

	sf::Texture stilTexture;

	sf::Texture walkTextures[2];
};
