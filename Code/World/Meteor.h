#pragma once
#include "Enemy.h"

// This is a hierarcy of meteor entities. Game has 3 types of meteors: small, medium, big.
// Big meteor when is destroing, splits into medium meteors, and the medium one splits
// into small ones. They all the same except number of points for their destroying, and
// different behavior when destroing.

class Meteor : public Enemy
{
public:
	Meteor(Configuration::Texture textureID, World& world, int pointsPorDstruction);

	virtual bool IsCollideWith(const Entity& other) const override;
	virtual void Update(float deltaTime) override;
};

class SmallMeteor : public Meteor
{
public:
	SmallMeteor(World& world);

	virtual void OnDestroy() override;
};

class MediumMeteor : public Meteor
{
public:
	MediumMeteor(World& world);

	virtual void OnDestroy() override;
};

class BigMeteor : public Meteor
{
public:
	BigMeteor(World& world);

	virtual void OnDestroy() override;
};