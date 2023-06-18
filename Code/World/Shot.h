#pragma once
#include "Entity.h"

// This is a hierarcy of shots which entities (player and enemies) can make.

class Shot : public Entity
{
public:
	Shot(Configuration::Texture textureID, World& world, float moveSpeed);

	virtual void Update(float deltaTime) override;

protected:
	float duration = 0;
};

class PlayerShot : public Shot
{
public:
	PlayerShot(Player& whoShoots);

	virtual bool IsCollideWith(const Entity& other) const override;
};

class SaucerShooter;

class SaucerShot : public Shot
{
public:
	SaucerShot(SaucerShooter& whoShoots);

	virtual bool IsCollideWith(const Entity& other) const override;
};