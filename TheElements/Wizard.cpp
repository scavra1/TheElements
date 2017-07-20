#include "Wizard.h"
#include <math.h>
#include <utility>
# define M_PI           3.14159265358979323846  /* pi */

Wizard::Wizard(int maxHealth, int maxMana)
{
	this->health = maxHealth;
	this->mana = this->maxMana = maxMana;

	if (!this->texture.loadFromFile("textures/wizard-still.png"))
		throw "Could not load texture in wizard loader.";

	this->wizardSprite.setOrigin(sf::Vector2f(21.5, 30));
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

	window.draw(this->wizardSprite);
}

void Wizard::TakeDamage(int damage)
{
	health -= damage;
}

bool Wizard::UseMana(double mana)
{
	if (this->mana < mana)
		return false;
	this->mana -= mana;
	return true;
}

void Wizard::IncreaseMana(double mana) {
	this->mana = std::min(this->mana + mana, this->maxMana);
}

bool Wizard::checkCollision(Block block)
{
	std::vector<std::pair<double, double>> corners = this->calculateCorners();
	if (block.containsPoint(corners[0].first, corners[0].second))
		return true;
	if (block.containsPoint(corners[1].first, corners[1].second))
		return true;
	if (block.containsPoint(corners[2].first, corners[2].second))
		return true;
	if (block.containsPoint(corners[3].first, corners[3].second))
		return true;
	return false;
}

bool Wizard::checkCollision(double pointX, double pointY)
{
	std::vector<std::pair<double, double>> corners = this->calculateCorners();
	return	pointX > std::min(corners[0].first, corners[2].first) &&
		pointX < std::max(corners[0].first, corners[2].first) &&
		pointY > std::min(corners[0].second, corners[2].second) &&
		pointY < std::max(corners[0].second, corners[2].second);
}

std::vector<std::pair<double, double>> Wizard::calculateCorners()
{
	double width = 43;
	double heightTop = 15;
	double heightBottom = 28;
	std::vector<std::pair<double, double>> corners;
	corners.push_back(std::pair<double, double>(this->xPosition - width / 2, this->yPosition - heightTop));
	corners.push_back(std::pair<double, double>(this->xPosition + width / 2, this->yPosition - heightTop));
	corners.push_back(std::pair<double, double>(this->xPosition + width / 2, this->yPosition + heightBottom));
	corners.push_back(std::pair<double, double>(this->xPosition - width / 2, this->yPosition + heightBottom));

	//Rotation
	double s = sin(this->rotation);
	double c = cos(this->rotation);
	for (int i = 0; i < 4; i++) {
		double x = (corners[i].first - this->xPosition) * c - (corners[i].second - this->yPosition) * s;
		double y = (corners[i].first - this->xPosition) * s + (corners[i].second - this->yPosition) * c;
		corners[i].first = x + this->xPosition;
		corners[i].second = y + this->yPosition;
	}
	return corners;
}

double Wizard::getHealth()
{
	return this->health;
}

double Wizard::getMana()
{
	return this->mana;
}

Particle Wizard::generateParticle()
{
	double leftDistance = 12.0;
	double frontDistance = 35.0;
	double dx = leftDistance * cos(this->rotation) - frontDistance * cos(this->rotation + M_PI / 2);
	double dy = leftDistance * sin(this->rotation) - frontDistance * sin(this->rotation + M_PI / 2);
	double particleSpeed = 10.0;
	double divergence = 5; //degrees
	double angle = this->rotation - M_PI / 2 + ((double)(rand() % 200 - 100) / 100.0) * (divergence * M_PI / 180.0);
	return Particle(this->xPosition + dx, this->yPosition + dy, particleSpeed * cos(angle), particleSpeed * sin(angle));
}

void Wizard::OnUpdate()
{
	this->wizardSprite.setRotation(this->rotation * 180 / M_PI);
	this->wizardSprite.setPosition(this->xPosition, this->yPosition);
}
