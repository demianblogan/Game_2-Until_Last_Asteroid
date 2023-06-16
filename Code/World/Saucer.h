#pragma once
#include "Enemy.h"

// This is a hierarcy of saucers entities. Game has 2 types of saucers: small and big.
// Big saucer can make shots on you, and the small one tries to reach you and destroy by
// exploding itself.

class Saucer : public Enemy
{
public:
	using Enemy::Enemy;

	Saucer(Configuration::Texture textureID, World& world, int pointsPorDstruction);

	virtual bool IsCollideWith(const Entity& other) const override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void OnDestroy() override;

	static void CreateNewSaucer(World& world);
};

class BigSaucer : public Saucer
{
public:
	BigSaucer(World& world);
};

class SmallSaucer : public Saucer
{
private:
	sf::Time timeSinceLastShoot;

public:
	SmallSaucer(World& world);

	virtual void Update(sf::Time deltaTime) override;
};