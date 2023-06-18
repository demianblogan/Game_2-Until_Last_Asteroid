#pragma once
#include <SFML/Graphics.hpp>
#include "../Configuration.h"

class World;

// The Entity class is the base class for all entities within the game world.
// It provides common properties and behaviours such as being drawable, 
// having a sprite, a position, and an alive status.
class Entity : public sf::Drawable
{
public:
	Entity(Configuration::Texture textureID, World& world);

	virtual ~Entity();

	template <typename... Args>
	void SetPosition(Args&&... args)
	{
		sprite.setPosition(std::forward<Args>(args)...);
	}

	const sf::Vector2f& GetPosition() const;

	World& GetWorld();
	const sf::Sprite& GetSprite() const;

	virtual bool IsAlive() const;
	virtual bool IsCollideWith(const Entity& other) const = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void OnDestroy();

protected:
	friend class Meteor;
	friend class Player;
	friend class Saucer;
	friend class PlayerShot;
	friend class EnemyShot;

	sf::Sprite sprite;
	sf::Vector2f moveDirection;
	float moveSpeed = 0;
	World& world;
	bool isAlive;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};