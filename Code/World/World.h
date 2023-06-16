#pragma once
#include <SFML/Graphics.hpp>
#include "../Configuration.h"

class Entity;

// class World contains all entities in the game (player, shots, enemies,...) and manages them.
class World : public sf::Drawable
{
public:
	World(unsigned int width, unsigned int height);

	~World();

	void Update(sf::Time deltaTime);

	void Add(Entity* entity);
	void Add(Configuration::Sound soundId);

	void Clear();
	bool IsEntityCollideWithOthers(const Entity& other) const;

	int GetExistingEntitiesCount() const;
	const std::list<Entity*> GetEntities() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	std::list<Entity*> entities;
	std::list<Entity*> temporaryEntities; // entities that are added in one update frame
	std::list<std::unique_ptr<sf::Sound>> sounds;

	const unsigned int width;
	const unsigned int height;

	void CheckEntityOutOfBounds(Entity& entity) const;
	void DestroyAllCollidedEntities() const;
	void EraseAllDeadEntities();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};