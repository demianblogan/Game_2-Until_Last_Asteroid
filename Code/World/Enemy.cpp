#include "Enemy.h"

#include "../Tools/Random.h"
#include "../Tools/Math.h"

Enemy::Enemy(Configuration::Texture textureID, World& world, int pointsPorDstruction)
	: Entity(textureID, world), pointsPorDstruction(pointsPorDstruction)
{
	// Random angle from 0 to 360 degrees (in radiands):
	float angleInRadians = Random::GenerateFloat(0.0f, 2.0f * Math::PI);

	// Convert the angle from polar coordinates to Cartesian coordinates:
	moveDirection = sf::Vector2f(std::cos(angleInRadians), std::sin(angleInRadians));
}

int Enemy::GetPointsForDestruction() const
{
	return pointsPorDstruction;
}

void Enemy::OnDestroy()
{
	Entity::OnDestroy();
	Configuration::AddScore(GetPointsForDestruction());
}