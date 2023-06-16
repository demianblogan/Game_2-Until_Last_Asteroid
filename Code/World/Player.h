#pragma once

#include "../Actions/TargetForActions.h"
#include "../World/Entity.h"
#include "../Configuration.h"

// Class Player contains everything that player's ship can do: moving flag, rotationg angle
// and timespan for shooting. Also it's a target for keyboard/mouse actions.
class Player : public Entity, public TargetForActions<Configuration::PlayerAction>
{
private:
	bool isMoving;
	int rotationOffset;
	sf::Time timeSinceLastShoot;

public:
	Player(World& world);

	void ProcessEvents();
	void Shoot();
	void JumpToHyperspace();

	virtual bool IsCollideWith(const Entity& other) const override;
	virtual void Update(sf::Time deltaTime);
	virtual void OnDestroy() override;
};