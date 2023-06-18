#include "Collision.h"

bool Collision::CheckCircleCollision(const sf::Sprite& first, const sf::Sprite& second)
{
	// Get the dimensions of the first sprite and scale them.
	sf::Vector2f rectangle1(static_cast<float>(first.getTextureRect().width), static_cast<float>(first.getTextureRect().height));
	rectangle1.x *= first.getScale().x;
	rectangle1.y *= first.getScale().y;

	// Get the dimensions of the second sprite and scale them.
	sf::Vector2f rectangle2(static_cast<float>(second.getTextureRect().width), static_cast<float>(second.getTextureRect().height));
	rectangle2.x *= second.getScale().x;
	rectangle2.y *= second.getScale().y;

	// Calculate the approximate radii of the first and second sprites.
	float radius1 = (rectangle1.x + rectangle1.y) / 4;
	float radius2 = (rectangle2.x + rectangle2.y) / 4;

	// Calculate the horizontal and vertical distances between the two sprites.
	float horDistance = first.getPosition().x - second.getPosition().x;
	float vertDistance = first.getPosition().y - second.getPosition().y;

	// Check if the distance between the two sprites is less than or equal to the sum of their radii.
	return (horDistance * horDistance) + (vertDistance * vertDistance) <= (radius1 + radius2) * (radius1 + radius2);
}