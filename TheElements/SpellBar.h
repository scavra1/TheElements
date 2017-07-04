#pragma once
#include <SFML\Graphics.hpp>
#include "Elements.h"

class SpellBar
{
public:

	SpellBar();

	bool IsSpellReady(Elements element);

	void UseSpell(Elements element);

	void OnUpdate();

	void OnDraw(sf::RenderWindow& window);

	void SetElementPosition(sf::Vector2f position, Elements element);

private:

	sf::Sprite fireSpellSprite;

	sf::Sprite waterSpellSprite;

	sf::Sprite shadowSpellSprite;

	sf::Sprite earthSpellSprite;

	sf::Sprite cooldownSheathSprite;


	sf::Texture fireSpellTexture;

	sf::Texture waterSpellTexture;

	sf::Texture shadowSpellTexture;

	sf::Texture earthSpellTexture;

	sf::Texture cooldownSheathTexture;

	
	sf::Clock fireSpellCooldown;

	sf::Clock waterSpellCooldown;

	sf::Clock shadowSpellCooldown;

	sf::Clock earthSpellCooldown;


	sf::Shader cooldownShader;

	sf::Shader spellShader;
};