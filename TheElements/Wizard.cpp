#include "Wizard.h"
#include <math.h>
#include <utility>
# define M_PI           3.14159265358979323846  /* pi */

/**
* Constructor. Sets wizard's max health and max mana
*/
Wizard::Wizard(int maxHealth, int maxMana)
{
	this->health = maxHealth;
	this->mana = this->maxMana = maxMana;

	if (!this->stilTexture.loadFromFile("textures/wizard-still.png"))
		throw "Could not load texture in wizard loader.";
	if (!this->walkTextures[0].loadFromFile("textures/wizard-run1.png"))
		throw "Could not load texture in wizard loader.";
	if (!this->walkTextures[1].loadFromFile("textures/wizard-run2.png"))
		throw "Could not load texture in wizard loader.";

	this->wizardSprite.setOrigin(sf::Vector2f(21.5, 30));
	this->wizardSprite.setTexture(this->stilTexture);
	this->rotation = M_PI / 2.0;
}

/**
* Sets wizard's position and rotation
*/
void Wizard::SetPosition(double x, double y, double r)
{
	this->xPosition = x;
	this->yPosition = y;
	this->rotation = r;
}

/**
* Moves wizard left (relative to its rotation) by a given distance
*/
void Wizard::MoveLeft(double displacement)
{
	this->yPosition -= displacement * cos(this->rotation - M_PI / 2);
	this->xPosition += displacement * sin(this->rotation - M_PI / 2);
}

/**
* Moves wizard right (relative to its rotation) by a given distance
*/
void Wizard::MoveRight(double displacement)
{
	this->yPosition -= displacement * cos(this->rotation + M_PI / 2);
	this->xPosition += displacement * sin(this->rotation + M_PI / 2);
}

/**
* Moves wizard backward (relative to its rotation) by a given distance
*/
void Wizard::MoveBackward(double displacement)
{
	this->yPosition -= displacement * cos(this->rotation + M_PI);
	this->xPosition += displacement * sin(this->rotation + M_PI);
	if (displacement != 0)
		this->isMoving = true;
}

/**
* Moves wizard forward (relative to its rotation) by a given distance
*/
void Wizard::MoveForward(double displacement)
{
	this->yPosition -= displacement * cos(this->rotation);
	this->xPosition += displacement * sin(this->rotation);
	if (displacement != 0)
		this->isMoving = true;
}

/**
* Rotates wizard anti-clockwise
*/
void Wizard::RotateLeft(double angle)
{
	this->rotation -= angle;
}

/**
* Rotates wizard clockwise
*/
void Wizard::RotateRight(double angle)
{
	this->rotation += angle;
}

/**
* Method that is responsible for drawing wizard on the screen
*/
void Wizard::OnDraw(sf::RenderTarget & window)
{
	const int flatsPerImage = 8;
	const int flats = 2;
	if (this->isMoving) {
		this->wizardSprite.setTexture(this->walkTextures[this->walkAnimationTimer / flatsPerImage]);
		this->walkAnimationTimer = (this->walkAnimationTimer + 1) % (flats * flatsPerImage);
	}
	else {
		this->wizardSprite.setTexture(this->stilTexture);
	}
	window.draw(this->wizardSprite);
}

/**
* Decreases wizard's health by a given amount
*/
void Wizard::TakeDamage(int damage)
{
	health -= damage;
}

/**
* Decreases wizard's mana by a given amount
*/
bool Wizard::UseMana(double mana)
{
	if (this->mana < mana)
		return false;
	this->mana -= mana;
	return true;
}


/**
* Increases wizard;s mana by a given amount
*/
void Wizard::IncreaseMana(double mana) {
	this->mana = std::min(this->mana + mana, this->maxMana);
}

/**
* Check if wizard collides with given block
*/
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


/**
* Check if wizard collides with a given point
*/
bool Wizard::checkCollision(double pointX, double pointY)
{
	std::vector<std::pair<double, double>> corners = this->calculateCorners();
	return	pointX > std::min(corners[0].first, corners[2].first) &&
		pointX < std::max(corners[0].first, corners[2].first) &&
		pointY > std::min(corners[0].second, corners[2].second) &&
		pointY < std::max(corners[0].second, corners[2].second);
}

/**
* Creates and returns vertices of wizard's collider
*/
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

/**
* Returns wizard's health
*/
double Wizard::getHealth()
{
	return this->health;
}

/**
* Returns wizard's mana
*/
double Wizard::getMana()
{
	return this->mana;
}

/**
* Returns new particle with appriopriate position and velocity 
*/
Particle Wizard::generateParticle(Elements type)
{
	double leftDistance, frontDistance, dx, dy, particleSpeed, divergence, angle;
	switch (type) {
	case Elements::Water:
		leftDistance = 0.0;
		frontDistance = 45.0;
		dx = leftDistance * cos(this->rotation) - frontDistance * cos(this->rotation + M_PI / 2);
		dy = leftDistance * sin(this->rotation) - frontDistance * sin(this->rotation + M_PI / 2);
		particleSpeed = 10.0;
		divergence = 5; //degrees
		angle = this->rotation - M_PI + ((double)(rand() % 200 - 100) / 100.0) * (divergence * M_PI / 180.0);
		return Particle(this->xPosition + dx, this->yPosition + dy, particleSpeed * cos(angle), particleSpeed * sin(angle), type);
	default:
		leftDistance = 12.0;
		frontDistance = 35.0;
		dx = leftDistance * cos(this->rotation) - frontDistance * cos(this->rotation + M_PI / 2);
		dy = leftDistance * sin(this->rotation) - frontDistance * sin(this->rotation + M_PI / 2);
		particleSpeed = 10.0;
		divergence = 5; //degrees
		angle = this->rotation - M_PI / 2 + ((double)(rand() % 200 - 100) / 100.0) * (divergence * M_PI / 180.0);
		return Particle(this->xPosition + dx, this->yPosition + dy, particleSpeed * cos(angle), particleSpeed * sin(angle), type);
	}
	
}

/**
* Method that should be called before each frame
*/
void Wizard::OnUpdate()
{
	this->wizardSprite.setRotation(this->rotation * 180 / M_PI);
	this->wizardSprite.setPosition(this->xPosition, this->yPosition);
	this->isMoving = false;
	this->lastXPosition = this->xPosition;
	this->lastYPosition = this->yPosition;
}
