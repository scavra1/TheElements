#include "Wizard.h"


Wizard::Wizard(int maxHealth, int maxMana)
{
	this->health = maxHealth;
	this->mana = maxMana;
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
