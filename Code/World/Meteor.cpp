#include "Meteor.h"
#include "World.h"
#include "../Physics/Collision.h"
#include "../Tools/Random.h"

#pragma region Meteor class

Meteor::Meteor(Configuration::Texture textureID, World& world, int pointsPorDstruction)
	: Enemy(textureID, world, pointsPorDstruction)
{ }

bool Meteor::IsCollideWith(const Entity& other) const
{
	// Meteors can move through each other. So we just check if they
	// collide with other meteors:
	if (dynamic_cast<const Meteor*>(&other) == nullptr)
		return Collision::CheckCircleCollision(sprite, other.sprite);
	else
		return false;
}

void Meteor::Update(float deltaTime)
{
	sprite.move(moveDirection * moveSpeed * deltaTime);
}

#pragma endregion

#pragma region SmallMeteor class

SmallMeteor::SmallMeteor(World& world)
	: Meteor((Configuration::Texture)Random::GenerateInt(
		int(Configuration::Texture::SmallMeteor1),
		int(Configuration::Texture::SmallMeteor4)
	), world, 100)
{
	moveSpeed = 300.0f;
}

void SmallMeteor::OnDestroy()
{
	Meteor::OnDestroy();
	world.Add(Configuration::Sound::SmallMeteorExplosion);
}

#pragma endregion

#pragma region MediumMeteor class

MediumMeteor::MediumMeteor(World& world)
	: Meteor((Configuration::Texture)Random::GenerateInt(
		int(Configuration::Texture::MediumMeteor1),
		int(Configuration::Texture::MediumMeteor2)
	), world, 60)
{
	moveSpeed = 200.0f;
}

void MediumMeteor::OnDestroy()
{
	Meteor::OnDestroy();

	int smallMeteorsCount = Random::GenerateInt(2, 3);
	for (int i = 0; i < smallMeteorsCount; i++)
	{
		SmallMeteor* meteor = new SmallMeteor(world);
		meteor->SetPosition(GetPosition());
		world.Add(meteor);
	}
	world.Add(Configuration::Sound::MediumMeteorExplosion);
}

#pragma endregion

#pragma region BigMeteor class

BigMeteor::BigMeteor(World& world)
	: Meteor((Configuration::Texture)Random::GenerateInt(
		int(Configuration::Texture::BigMeteor1),
		int(Configuration::Texture::BigMeteor4)
	), world, 20)
{
	moveSpeed = 100.0f;
}

void BigMeteor::OnDestroy()
{
	Meteor::OnDestroy();

	int mediumMeteorsCount = Random::GenerateInt(2, 3);
	for (int i = 0; i < mediumMeteorsCount; i++)
	{
		MediumMeteor* meteor = new MediumMeteor(world);
		meteor->SetPosition(GetPosition());
		world.Add(meteor);
	}
	world.Add(Configuration::Sound::BigMeteorExplosion);
}

#pragma endregion