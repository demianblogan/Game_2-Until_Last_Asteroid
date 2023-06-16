#pragma once
#include "Entity.h"

// class Enemy extends Enity class with next functions
class Enemy : public Entity
{
public:
	Enemy(Configuration::Texture textureID, World& world, int pointsPorDstruction);

	virtual int GetPointsForDestruction() const;
	virtual void OnDestroy();

private:
	int pointsPorDstruction;
};