#include "Wizard.h"


Wizard::Wizard(int maxHealth, int maxMana)
{
	this->health = maxHealth;
	this->mana = maxMana;

	if (!this->texture.loadFromFile("textures/wizard.png"))
		throw "Could not load texture in wizard loader.";

	this->wizardSprite.setTexture(this->texture);
	this->rotation = 90;

}

void Wizard::MoveLeft()
{
	this->xPosition -= 1;
}

void Wizard::MoveRight()
{
	this->xPosition += 1;
}

void Wizard::MoveDown()
{
	this->yPosition += 1;
}

void Wizard::MoveUp()
{
	this->yPosition -= 1;
}

void Wizard::StartAttack()
{

}

void Wizard::StopAttack()
{

}

void Wizard::RotateLeft()
{
	this->rotation += 5;
}

void Wizard::RotateRight()
{
	this->rotation -= 5;
}



void Wizard::TakeDamage(int damage)
{
	health -= damage;
}

int Wizard::getHealth()
{
	return this->health;
}

int Wizard::getMana()
{
	return this->mana;
}

void Wizard::OnUpdate()
{
	this->wizardSprite.setRotation((float)this->rotation / 360);
	this->wizardSprite.setPosition(this->xPosition, this->yPosition);
}

void Wizard::OnDraw(sf::RenderWindow& window)
{
	window.draw(this->wizardSprite);
}
