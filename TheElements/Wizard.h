#pragma once
#include "ResourceBar.h"
#include "ManaBar.h"
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

	void OnDraw(sf::RenderWindow & window);

	void TakeDamage(int damage);

	int getHealth();

	int getMana();

private:
	double xPosition;

	double yPosition;

	double rotation;

	int health;

	int mana;

	sf::Sprite wizardSprite;

	sf::Texture texture;
};
