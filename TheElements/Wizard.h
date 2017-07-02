#pragma once
#include "ResourceBar.h"
#include "ManaBar.h"
class Wizard
{

public:
	Wizard(int maxHealth, int maxMana);

	void MoveLeft();

	void MoveRight();

	void MoveDown();

	void MoveUp();

	void StartAttack();

	void StopAttack();

	void RotateLeft();

	void RotateRight();

	void OnUpdate();

	void TakeDamage(int damage);

	int getHealth();

	int getMana();

	void OnDraw(sf::RenderWindow& window);

private:
	int xPosition;

	int yPosition;

	int rotation;

	int health;

	int mana;

	sf::Sprite wizardSprite;

	sf::Texture texture;
};
