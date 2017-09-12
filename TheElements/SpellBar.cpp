#include "SpellBar.h"

SpellBar::SpellBar()
{
	if (!this->fireSpellTexture.loadFromFile("textures/fireSpell2.png"))
		throw "Could not load spell textures in spell bar loader.";

	if(!this->waterSpellTexture.loadFromFile("textures/waterSpell2.png"))
		throw "Could not load spell textures in spell bar loader.";

	if(!this->shadowSpellTexture.loadFromFile("textures/shadowSpell2.png"))
		throw "Could not load spell textures in spell bar loader.";
	
	if(!this->earthSpellTexture.loadFromFile("textures/earthSpell2.png"))
		throw "Could not load spell textures in spell bar loader.";


	if (!this->cooldownSheathTexture.loadFromFile("textures/cooldownSheath2.png"))
		throw "Could not load spell textures in spell bar loader.";


	if (!this->cooldownShader.loadFromFile("shaders/cooldown.frag", sf::Shader::Type::Fragment))
		throw "Could not compile shader in spell bar loader.";

	if (!this->spellShader.loadFromFile("shaders/spell.frag", sf::Shader::Type::Fragment))
		throw "Could not compile shader in spell bar loader.";


	this->fireSpellSprite.setTexture(this->fireSpellTexture);
	this->waterSpellSprite.setTexture(this->waterSpellTexture);
	this->shadowSpellSprite.setTexture(this->shadowSpellTexture);
	this->earthSpellSprite.setTexture(this->earthSpellTexture);


	this->cooldownSheathSprite.setTexture(this->cooldownSheathTexture);

	this->fireSpellCooldown.restart();
	this->waterSpellCooldown.restart();
	this->shadowSpellCooldown.restart();

	this->cooldownShader.setUniform("sheathSize", (int)this->cooldownSheathTexture.getSize().x);
}

bool SpellBar::IsSpellReady(Elements element)
{
	switch (element)
	{
	case Elements::Fire: return this->fireSpellCooldown.getElapsedTime().asSeconds() > 3.0f;
	case Elements::Water: return this->waterSpellCooldown.getElapsedTime().asSeconds() > 3.0f;
	case Elements::Earth: return this->earthSpellCooldown.getElapsedTime().asSeconds() > 3.0f;
	case Elements::Shadow: return this->shadowSpellCooldown.getElapsedTime().asSeconds() > 3.0f;
	}
}

void SpellBar::UseSpell(Elements element)
{
	switch (element)
	{
	case Elements::Fire: this->fireSpellCooldown.restart(); break;
	case Elements::Water: this->waterSpellCooldown.restart(); break;
	case Elements::Earth: this->earthSpellCooldown.restart(); break;
	case Elements::Shadow: this->shadowSpellCooldown.restart(); break;
	}
}

void SpellBar::OnUpdate()
{
}

void SpellBar::OnDraw(sf::RenderTarget& window)
{
	
	
	this->cooldownShader.setUniform("cooldown", this->fireSpellCooldown.getElapsedTime().asSeconds() / 5.0f);
	this->cooldownShader.setUniform("beginPosition", this->fireSpellSprite.getPosition().x);
	this->cooldownSheathSprite.setPosition(this->fireSpellSprite.getPosition());
	
	window.draw(this->fireSpellSprite, sf::RenderStates(&this->spellShader));
	window.draw(this->cooldownSheathSprite, sf::RenderStates(&this->cooldownShader));

	this->cooldownShader.setUniform("cooldown", this->waterSpellCooldown.getElapsedTime().asSeconds() / 5.0f);
	this->cooldownShader.setUniform("beginPosition", this->waterSpellSprite.getPosition().x);
	this->cooldownSheathSprite.setPosition(this->waterSpellSprite.getPosition());

	window.draw(this->waterSpellSprite, sf::RenderStates(&this->spellShader));
	window.draw(this->cooldownSheathSprite, sf::RenderStates(&this->cooldownShader));

	this->cooldownShader.setUniform("cooldown", this->shadowSpellCooldown.getElapsedTime().asSeconds() / 5.0f);
	this->cooldownShader.setUniform("beginPosition", this->shadowSpellSprite.getPosition().x);
	this->cooldownSheathSprite.setPosition(this->shadowSpellSprite.getPosition());

	window.draw(this->shadowSpellSprite, sf::RenderStates(&this->spellShader));
	window.draw(this->cooldownSheathSprite, sf::RenderStates(&this->cooldownShader));

	this->cooldownShader.setUniform("cooldown", this->earthSpellCooldown.getElapsedTime().asSeconds() / 5.0f);
	this->cooldownShader.setUniform("beginPosition", this->earthSpellSprite.getPosition().x);
	this->cooldownSheathSprite.setPosition(this->earthSpellSprite.getPosition());

	window.draw(this->earthSpellSprite, sf::RenderStates(&this->spellShader));
	window.draw(this->cooldownSheathSprite, sf::RenderStates(&this->cooldownShader));
}

void SpellBar::SetElementPosition(sf::Vector2f position, Elements element)
{
	switch (element)
	{
	
	case Elements::Fire: this->fireSpellSprite.setPosition(position); break;
	case Elements::Water: this->waterSpellSprite.setPosition(position); break;
	case Elements::Earth: this->earthSpellSprite.setPosition(position); break;
	case Elements::Shadow: this->shadowSpellSprite.setPosition(position); break;
	}
}
