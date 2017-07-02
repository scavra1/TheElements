#include "Wizard.h"


Wizard::Wizard(int maxHealth, int maxMana)
{
	this->health = maxHealth;
	this->mana = maxMana;
}

void Wizard::SetPosition(int x, int y)
{
	this->xPosition = x;
	this->yPosition = y;
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

void Wizard::OnUpdate()
{

}

void Wizard::OnDraw(sf::RenderWindow & window)
{
	sf::CircleShape shape(40, 3);
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(this->xPosition, this->yPosition);
	window.draw(shape);
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
