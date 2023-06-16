#include "Saucer.h"

#include "Meteor.h"
#include "Player.h"
#include "Shot.h"
#include "World.h"
#include "../Physics/Collision.h"
#include "../Tools/Random.h"

#pragma region class Saucer

Saucer::Saucer(Configuration::Texture textureID, World& world, int pointsPorDstruction)
	: Enemy(textureID, world, pointsPorDstruction)
{ }

bool Saucer::IsCollideWith(const Entity& other) const
{
	// Saucers can't collide with their bullets. So we just check if they
	// collide with other entities:
	if (dynamic_cast<const SaucerShot*>(&other) == nullptr)
		return Collision::CheckCircleCollision(sprite, other.sprite);

	return false;
}

void Saucer::Update(sf::Time deltaTime)
{
	float deltaTime_asSeconds = deltaTime.asSeconds();

	// Find the nearest entity:
	Entity* neareastEntity = nullptr;
	float nearestDistance = 300.0f;

	for (Entity* entityPtr : world.GetEntities())
	{
		if (entityPtr != this &&
			(dynamic_cast<const Meteor*>(entityPtr) != nullptr || dynamic_cast<const PlayerShot*>(entityPtr) != nullptr))
		{
			float horizontalDistance = GetPosition().x - entityPtr->GetPosition().x;
			float verticalDistance = GetPosition().y - entityPtr->GetPosition().y;

			float distance = std::sqrt(horizontalDistance * horizontalDistance + verticalDistance * verticalDistance);

			if (distance < nearestDistance)
			{
				nearestDistance = distance;
				neareastEntity = entityPtr;
			}
		}
	}

	if (neareastEntity != nullptr)
	{
		sf::Vector2f disntaceToEntity = neareastEntity->GetPosition() - GetPosition();

		// Calculate the angle between the positive x-axis and the vector that points
		// from the current position to neareastEntity. (range [-pi...pi] or [-180, 180]):
		float angleInRadians = std::atan2(disntaceToEntity.y, disntaceToEntity.x);

		// Convert the angle from polar coordinates to Cartesian coordinates, and
		// set the result to moveSpeed:
		moveSpeed -= sf::Vector2f(std::cos(angleInRadians), std::sin(angleInRadians)) * 300.0f * deltaTime_asSeconds;
	}
	else // it's the player
	{
		sf::Vector2f disntaceToPlayer = Configuration::player->GetPosition() - GetPosition();

		// Calculate the angle between the positive x-axis and the vector that points
		// from the current position to disntaceToPlayer. (range [-pi...pi] or [-180, 180]):
		float angleInRadians = std::atan2(disntaceToPlayer.y, disntaceToPlayer.x);

		// Convert the angle from polar coordinates to Cartesian coordinates, and
		// set the result to moveSpeed:
		moveSpeed += sf::Vector2f(std::cos(angleInRadians), std::sin(angleInRadians)) * 100.0f * deltaTime_asSeconds;
	}

	sprite.move(moveSpeed * deltaTime_asSeconds);
}

void Saucer::OnDestroy()
{
	Enemy::OnDestroy();
	world.Add(Configuration::Sound::Boom2);
}

void Saucer::CreateNewSaucer(World& world)
{
	Saucer* newSoucer = nullptr;
	if (Random::GenerateFloat(0.0f, 1.0f) > Configuration::GetScore() / 40'000.0f)
		newSoucer = new BigSaucer(world);
	else
		newSoucer = new SmallSaucer(world);

	// New saucer will appear on the top.
	newSoucer->SetPosition(
		Random::GenerateInt(0, 1) * world.GetWidth(),
		Random::GenerateInt(0, world.GetHeight())
	);

	world.Add(newSoucer);
}

#pragma endregion

#pragma region class BigSaucer

BigSaucer::BigSaucer(World& world)
	: Saucer(Configuration::Texture::BigEnemySaucer, world, 50)
{
	world.Add(Configuration::Sound::SaucerSpawn1);
	moveSpeed *= 300.0f;
}

#pragma endregion

#pragma region class SmallSaucer

SmallSaucer::SmallSaucer(World& world)
	: Saucer(Configuration::Texture::SmallEnemySaucer, world, 200)
{
	timeSinceLastShoot = sf::Time::Zero;
	world.Add(Configuration::Sound::SaucerSpawn2);
	moveSpeed * 400.0f;
}

void SmallSaucer::Update(sf::Time deltaTime)
{
	Saucer::Update(deltaTime);

	// Every 1.5 second make a shot on the player:
	timeSinceLastShoot += deltaTime;
	if (timeSinceLastShoot > sf::seconds(1.5))
	{
		if (Configuration::player != nullptr)
			world.Add(new SaucerShot(*this));

		timeSinceLastShoot = sf::Time::Zero;
	}
}

#pragma endregion