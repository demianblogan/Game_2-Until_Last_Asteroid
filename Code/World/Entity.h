#pragma once
#include <SFML/Graphics.hpp>
#include "../Configuration.h"

class World;

// class Entity is a base class of all entities hierarchy in the game world, and contains
// same properties for all entites (drawing possibily, sprite, etc.).
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
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void OnDestroy();

protected:
	friend class Meteor;
	friend class Player;
	friend class Saucer;
	friend class PlayerShot;
	friend class EnemyShot;

	sf::Sprite sprite;
	sf::Vector2f moveSpeed; // This field is a direction of the entity + its moving speed
	World& world;
	bool isAlive;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};