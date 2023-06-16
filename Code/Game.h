#pragma once

#include <SFML/Graphics.hpp>
#include "World/World.h"

// class Game is the main class that manages processing input events, updating game
// entities and rendering them onto the game window.
class Game
{
public:
	Game();

	void Run();

private:
	const sf::String WINDOW_TITLE = "Until last asteroid";
	sf::VideoMode windowSize;
	sf::RenderWindow window;

	World world;

	sf::Time timeUntilNextEnemySaucerAppears = sf::Time::Zero;
	sf::Text textPromptForUser;
	static constexpr int TEXT_RROMPT_FOR_USER_FONT_SIZE = 70;

	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();
	void Reset();
	void InitializeLevel();
};