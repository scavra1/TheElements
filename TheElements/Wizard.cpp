#include "Wizard.h"
#include <math.h>
# define M_PI           3.14159265358979323846  /* pi */


Wizard::Wizard(int maxHealth, int maxMana)
{
	this->health = maxHealth;
	this->mana = maxMana;

	if (!this->texture.loadFromFile("textures/wizard.png"))
		throw "Could not load texture in wizard loader.";

	this->wizardSprite.setTexture(this->texture);
	this->rotation = M_PI / 2.0;

}

void Wizard::SetPosition(double x, double y, double r)
{
	this->xPosition = x;
	this->yPosition = y;
	this->rotation = r;
}

void Wizard::MoveLeft(double displacement)
{
	this->yPosition -= displacement * cos(this->rotation - M_PI / 2);
	this->xPosition += displacement * sin(this->rotation - M_PI / 2);
}

void Wizard::MoveRight(double displacement)
{
	this->yPosition -= displacement * cos(this->rotation + M_PI / 2);
	this->xPosition += displacement * sin(this->rotation + M_PI / 2);
}

void Wizard::MoveBackward(double displacement)
{
	this->yPosition -= displacement * cos(this->rotation + M_PI);
	this->xPosition += displacement * sin(this->rotation + M_PI);
}

void Wizard::MoveForward(double displacement)
{
	this->yPosition -= displacement * cos(this->rotation);
	this->xPosition += displacement * sin(this->rotation);
}

void Wizard::StartAttack()
{

}

void Wizard::StopAttack()
{

}

void Wizard::RotateLeft(double angle)
{
	this->rotation -= angle;
}

void Wizard::RotateRight(double angle)
{
	this->rotation += angle;
}



void Wizard::OnDraw(sf::RenderWindow & window)
{
	sf::CircleShape shape(40, 3);
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(this->xPosition, this->yPosition);
	shape.rotate(this->rotation * 180.0 / M_PI);
	window.draw(shape);

	//window.draw(this->wizardSprite);
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
