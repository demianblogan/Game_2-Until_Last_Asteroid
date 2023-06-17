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

void Saucer::Update(float deltaTime)
{
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
		moveSpeed -= sf::Vector2f(std::cos(angleInRadians), std::sin(angleInRadians)) * 300.0f * deltaTime;
	}
	else // it's the player
	{
		sf::Vector2f disntaceToPlayer = Configuration::player->GetPosition() - GetPosition();

		// Calculate the angle between the positive x-axis and the vector that points
		// from the current position to disntaceToPlayer. (range [-pi...pi] or [-180, 180]):
		float angleInRadians = std::atan2(disntaceToPlayer.y, disntaceToPlayer.x);

		// Convert the angle from polar coordinates to Cartesian coordinates, and
		// set the result to moveSpeed:
		moveSpeed += sf::Vector2f(std::cos(angleInRadians), std::sin(angleInRadians)) * 100.0f * deltaTime;
	}

	sprite.move(moveSpeed * deltaTime);
}

void Saucer::OnDestroy()
{
	Enemy::OnDestroy();
	world.Add(Configuration::Sound::EnemySaucerExplosion);
}

void Saucer::CreateNewSaucer(World& world)
{
	Saucer* newSoucer = nullptr;
	if (Random::GenerateFloat(0.0f, 1.0f) > Configuration::GetScore() / 40'000.0f)
		newSoucer = new SaucerKamikaze(world);
	else
		newSoucer = new SaucerShooter(world);

	// New saucer will appear on the top.
	newSoucer->SetPosition(
		Random::GenerateInt(0, 1) * world.GetWidth(),
		Random::GenerateInt(0, world.GetHeight())
	);

	world.Add(newSoucer);
}

#pragma endregion

#pragma region class SaucerKamikaze

SaucerKamikaze::SaucerKamikaze(World& world)
	: Saucer(Configuration::Texture::BigEnemySaucer, world, 50)
{
	world.Add(Configuration::Sound::SaucerKamikazeSpawn);
	moveSpeed *= 300.0f;
}

#pragma endregion

#pragma region class SaucerShooter

SaucerShooter::SaucerShooter(World& world)
	: Saucer(Configuration::Texture::SmallEnemySaucer, world, 200)
{
	timeSinceLastShoot = 0;
	world.Add(Configuration::Sound::SaucerShooterSpawn);
	moveSpeed *= 400.0f;
}

void SaucerShooter::Update(float deltaTime)
{
	Saucer::Update(deltaTime);

	// Every 1.5 second make a shot on the player:
	timeSinceLastShoot += deltaTime;
	if (timeSinceLastShoot > 1.5f)
	{
		if (Configuration::player != nullptr)
			world.Add(new SaucerShot(*this));

		timeSinceLastShoot = 0;
	}
}

#pragma endregion