#pragma once
#include<SFML\Graphics.hpp>
class ResourceBar
{
public:

	ResourceBar(int startLoad, int maxCapacity);
	
	void AddResource(int value);

	void SubtractResource(int value);

	void SetPosition(sf::Vector2f position);

	void OnUpdate();

	void OnDraw(sf::RenderWindow& window);

private:

	int maximumCapacity;

	int toSubtract;

	int load;

	sf::Sprite barSprite;

	sf::Texture texture;

	sf::Shader shader;
};