#include "Saucer.h"

#include "Meteor.h"
#include "Player.h"
#include "Shot.h"
#include "World.h"
#include "../Physics/Collision.h"
#include "../Tools/Random.h"

#pragma region class Saucer

Saucer::Saucer(Configuration::Texture textureID, World& world, int pointsPorDstruction, float moveSpeed)
	: Enemy(textureID, world, pointsPorDstruction)
{
	this->moveSpeed = moveSpeed;
}

bool Saucer::IsCollideWith(const Entity& other) const
{
	// Saucers can collide only with player and his shots.
	if (dynamic_cast<const Player*>(&other) != nullptr || dynamic_cast<const PlayerShot*>(&other) != nullptr)
		return Collision::CheckCircleCollision(sprite, other.sprite);

	return false;
}

void Saucer::Update(float deltaTime)
{
	sf::Vector2f disntaceToPlayer = Configuration::player->GetPosition() - GetPosition();

	// Calculate the angle between the positive x-axis and the vector that points
	// from the current position to player's. (range [-pi...pi] or [-180, 180]):
	float angleInRadians = std::atan2(disntaceToPlayer.y, disntaceToPlayer.x);

	// Convert the angle from polar coordinates to Cartesian coordinates, and
	// set the result to moveDirection:
	moveDirection = sf::Vector2f(std::cos(angleInRadians), std::sin(angleInRadians));

	sprite.move(moveDirection * moveSpeed * deltaTime);
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
	: Saucer(Configuration::Texture::BigEnemySaucer, world, 50, 700.0f)
{
	world.Add(Configuration::Sound::SaucerKamikazeSpawn);
}

#pragma endregion

#pragma region class SaucerShooter

SaucerShooter::SaucerShooter(World& world)
	: Saucer(Configuration::Texture::SmallEnemySaucer, world, 200, 400.0f)
{
	timeSinceLastShoot = 0;
	world.Add(Configuration::Sound::SaucerShooterSpawn);
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