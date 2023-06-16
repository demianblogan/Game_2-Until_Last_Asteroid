#include "Entity.h"

Entity::Entity(Configuration::Texture textureID, World& world)
	: world(world), isAlive(true)
{
	sf::Texture& texture = Configuration::textures.Get(textureID);
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}

Entity::~Entity()
{ }

const sf::Vector2f& Entity::GetPosition() const
{
	return sprite.getPosition();
}

World& Entity::GetWorld()
{
	return world;
}

const sf::Sprite& Entity::GetSprite() const
{
	return sprite;
}

bool Entity::IsAlive() const
{
	return isAlive;
}

void Entity::OnDestroy()
{
	isAlive = false;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}