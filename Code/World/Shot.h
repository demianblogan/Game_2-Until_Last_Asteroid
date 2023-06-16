#pragma once
#include "Entity.h"

// This is a hierarcy of shots which entities (player and enemies) can make.

class Shot : public Entity
{
public:
	using Entity::Entity;

	Shot(Configuration::Texture textureID, World& world);

	virtual void Update(sf::Time deltaTime) override;

protected:
	sf::Time duration;
};

class PlayerShot : public Shot
{
public:
	PlayerShot(Player& whoShoots);

	virtual bool IsCollideWith(const Entity& other) const override;
};

class SmallSaucer;

class SaucerShot : public Shot
{
public:
	SaucerShot(SmallSaucer& whoShoots);

	virtual bool IsCollideWith(const Entity& other) const override;
};