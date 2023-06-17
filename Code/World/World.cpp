#include "World.h"

#include "Entity.h"

World::World(unsigned int width, unsigned int height)
	: width(width), height(height)
{ }

World::~World()
{
	Clear();
}

void World::Update(float deltaTime)
{
	if (temporaryEntities.size() > 0)
		entities.splice(entities.end(), temporaryEntities);

	for (Entity* entityPtr : entities)
	{
		Entity& entity = *entityPtr;
		entity.Update(deltaTime);

		CheckEntityOutOfBounds(entity);
	}

	DestroyAllCollidedEntities();
	EraseAllDeadEntities();

	sounds.remove_if(
		[](const std::unique_ptr<sf::Sound>& sound)
		{
			return sound->getStatus() != sf::SoundSource::Status::Playing;
		}
	);
}

void World::Add(Entity* entity)
{
	temporaryEntities.push_back(entity);
}

void World::Add(Configuration::Sound soundId)
{
	auto soundPtr = std::make_unique<sf::Sound>(Configuration::sounds.Get(soundId));
	soundPtr->setAttenuation(0);
	soundPtr->play();

	sounds.emplace_back(std::move(soundPtr));
}

void World::Clear()
{
	for (Entity* entity : entities)
		delete entity;
	entities.clear();

	for (Entity* entity : temporaryEntities)
		delete entity;
	temporaryEntities.clear();

	sounds.clear();
}

bool World::IsEntityCollideWithOthers(const Entity& entity) const
{
	for (Entity* entityPtr : entities)
		if (entity.IsCollideWith(*entityPtr))
			return true;

	return false;
}

int World::GetExistingEntitiesCount() const
{
	return static_cast<int>(entities.size() + temporaryEntities.size());
}

const std::list<Entity*> World::GetEntities() const
{
	return entities;
}

int World::GetWidth() const
{
	return width;
}

int World::GetHeight() const
{
	return height;
}

void World::CheckEntityOutOfBounds(Entity& entity) const
{
	// If any entity is out of world's bounds - move it to
	// the other side of it:
	sf::Vector2f position = entity.GetPosition();
	if (position.x < 0)
		position.x = float(width);
	else if (position.x > width)
		position.x = 0;

	if (position.y < 0)
		position.y = float(height);
	else if (position.y > height)
		position.y = 0;

	entity.SetPosition(position);
}

void World::DestroyAllCollidedEntities() const
{
	for (auto outerIterator = entities.cbegin(), end = entities.cend(); outerIterator != end; ++outerIterator)
	{
		Entity& entity1 = **outerIterator;
		auto innterIterator = outerIterator;
		++innterIterator;

		for (; innterIterator != end; ++innterIterator)
		{
			Entity& entity2 = **innterIterator;

			if (entity1.IsAlive() && entity1.IsCollideWith(entity2))
				entity1.OnDestroy();

			if (entity2.IsAlive() && entity2.IsCollideWith(entity1))
				entity2.OnDestroy();
		}
	}
}

void World::EraseAllDeadEntities()
{
	for (auto entityIterator = entities.begin(); entityIterator != entities.end();)
	{
		if (!(*entityIterator)->IsAlive())
		{
			delete* entityIterator;
			entityIterator = entities.erase(entityIterator);
		}
		else
		{
			++entityIterator;
		}
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Entity* entity : entities)
		target.draw(*entity, states);
}