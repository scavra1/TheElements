#include <SFML\Graphics.hpp>

typedef struct
{
	sf::Keyboard::Key MoveLeft;
	
	sf::Keyboard::Key moveRight;

	sf::Keyboard::Key RotateLeft;

	sf::Keyboard::Key RotateRight;

	sf::Keyboard::Key Attack;

	sf::Keyboard::Key ChangeElement;

} PlayerConfig;