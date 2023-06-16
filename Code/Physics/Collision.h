#pragma once
#include <SFML/Graphics.hpp>

// Class Collision is just one-method class that provide the collision detection method for
// two sprites.
class Collision
{
public:
	Collision() = delete;

	static bool CheckCircleCollision(const sf::Sprite& first, const sf::Sprite& second);
};