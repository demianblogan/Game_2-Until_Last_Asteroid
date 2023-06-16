#include "Collision.h"

bool Collision::CheckCircleCollision(const sf::Sprite& first, const sf::Sprite& second)
{
	sf::Vector2f rectangle1(static_cast<float>(first.getTextureRect().width), static_cast<float>(first.getTextureRect().height));
	rectangle1.x *= first.getScale().x;
	rectangle1.y *= first.getScale().y;

	sf::Vector2f rectangle2(static_cast<float>(second.getTextureRect().width), static_cast<float>(second.getTextureRect().height));
	rectangle2.x *= second.getScale().x;
	rectangle2.y *= second.getScale().y;

	float radius1 = (rectangle1.x + rectangle1.y) / 4;
	float radius2 = (rectangle2.x + rectangle2.y) / 4;

	float horDistance = first.getPosition().x - second.getPosition().x;  // horizontal distance
	float vertDistance = first.getPosition().y - second.getPosition().y; // vertical distance

	return std::sqrt(horDistance * horDistance + vertDistance * vertDistance) <= radius1 + radius2;
}
