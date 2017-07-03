#include "SpellBar.h"

SpellBar::SpellBar()
{
	if (!this->fireSpellTexture.loadFromFile("textures/fireSpell.png"))
		throw "Could not load spell textures in spell bar loader.";

	//|| !this->waterSpellTexture.loadFromFile("textures/waterSpell.png")
	//|| !this->airSpellTexture.loadFromFile("textures/airSpell.png")
	//|| !this->earthSpellTexture.loadFromFile("textures/earthSpell.png")

	if (!this->cooldownSheathTexture.loadFromFile("textures/cooldownSheath.png"))
		throw "Could not load spell textures in spell bar loader.";


	if (!this->cooldownShader.loadFromFile("shaders/cooldown.frag", sf::Shader::Type::Fragment))
		throw "Could not compile shader in spell bar loader.";

	if (!this->spellShader.loadFromFile("shaders/spell.frag", sf::Shader::Type::Fragment))
		throw "Could not compile shader in spell bar loader.";


	this->fireSpellSprite.setTexture(this->fireSpellTexture);
	//this->waterSpellSprite.setTexture(this->waterSpellTexture);
	//this->airSpellSprite.setTexture(this->airSpellTexture);
	//this->earthSpellSprite.setTexture(this->earthSpellTexture);


	this->cooldownSheathSprite.setTexture(this->cooldownSheathTexture);

	this->fireSpellCooldown.restart();
	this->cooldownShader.setUniform("sheathSize", (int)fireSpellTexture.getSize().x);
}

bool SpellBar::IsSpellReady(Elements element)
{
	switch (element)
	{
	case Elements::Air: return this->airSpellCooldown.getElapsedTime().asSeconds() > 3.0f;
	case Elements::Fire: return this->fireSpellCooldown.getElapsedTime().asSeconds() > 3.0f;
	case Elements::Water: return this->waterSpellCooldown.getElapsedTime().asSeconds() > 3.0f;
	case Elements::Earth: return this->earthSpellCooldown.getElapsedTime().asSeconds() > 3.0f;
	}
}

void SpellBar::UseSpell(Elements element)
{
	switch (element)
	{
	case Elements::Air: this->airSpellCooldown.restart(); break;
	case Elements::Fire: this->fireSpellCooldown.restart(); break;
	case Elements::Water: this->waterSpellCooldown.restart(); break;
	case Elements::Earth: this->earthSpellCooldown.restart(); break;
	}
}

void SpellBar::OnUpdate()
{
}

void SpellBar::OnDraw(sf::RenderWindow& window)
{
	//this->cooldownShader.setUniform("cooldown", airSpellCooldown.getElapsedTime().asSeconds() / 3.0f);
	//window.draw(this->airSpellSprite, sf::RenderStates(&this->cooldownShader));
	
	this->cooldownShader.setUniform("cooldown", fireSpellCooldown.getElapsedTime().asSeconds() / 5.0f);
	this->cooldownShader.setUniform("beginPosition", fireSpellSprite.getPosition().x);
	this->cooldownSheathSprite.setPosition(fireSpellSprite.getPosition());
	
	window.draw(this->fireSpellSprite, sf::RenderStates(&this->spellShader));
	window.draw(this->cooldownSheathSprite, sf::RenderStates(&this->cooldownShader));
	//this->cooldownShader.setUniform("cooldown", waterSpellCooldown.getElapsedTime().asSeconds() / 3.0f);
	//window.draw(this->waterSpellSprite, sf::RenderStates(&this->cooldownShader));

	//this->cooldownShader.setUniform("cooldown", earthSpellCooldown.getElapsedTime().asSeconds() / 3.0f);
	//window.draw(this->earthSpellSprite, sf::RenderStates(&this->cooldownShader));
}

void SpellBar::SetElementPosition(sf::Vector2f position, Elements element)
{
	switch (element)
	{
	case Elements::Air: airSpellSprite.setPosition(position); break;
	case Elements::Fire: fireSpellSprite.setPosition(position); break;
	case Elements::Water: waterSpellSprite.setPosition(position); break;
	case Elements::Earth: earthSpellSprite.setPosition(position); break;
	}
}
