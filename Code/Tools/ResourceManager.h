#pragma once
#include <unordered_map>
#include <SFML/Audio.hpp>

// class ResourceManager is a tool for containing sfml resources and
// easily managing them. SFML has clases like sf::Sound, sf::Font,
// sf::Shader, sf::Picture, sf::Image, sf::Sprite, etc. and they all have
// same interface.
template <typename Resource, typename Identifier>
class ResourceManager
{
public:
	template <typename... Args>
	void Load(const Identifier& id, Args&&... args)
	{
		auto ptr = std::make_unique<Resource>();
		if (!ptr->loadFromFile(std::forward<Args>(args)...))
			throw std::runtime_error("Failed to load file");

		resourceMap.emplace(id, std::move(ptr));
	}

	Resource& Get(const Identifier& id) const
	{
		return *resourceMap.at(id);
	}

private:
	std::unordered_map< Identifier, std::unique_ptr<Resource>> resourceMap;
};

// This specialization is created because sf::Music has method "openFromFile",
// while other SFML classes have methods "loadFromFile".
template <typename Identifier>
class ResourceManager<sf::Music, Identifier>
{
public:
	template <typename... Args>
	void Load(const Identifier& id, Args&&... args)
	{
		auto ptr = std::make_unique<sf::Music>();
		if (!ptr->openFromFile(std::forward<Args>(args)...))
			throw std::runtime_error("Failed to open music file");

		musicMap.emplace(id, std::move(ptr));
	}

	sf::Music& Get(const Identifier& id) const
	{
		return *musicMap.at(id);
	}

private:
	std::unordered_map<Identifier, std::unique_ptr<sf::Music>> musicMap;
};