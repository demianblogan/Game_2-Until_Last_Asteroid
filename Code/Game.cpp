#include "Game.h"

#include "World/Player.h"
#include "World/Meteor.h"
#include "World/Saucer.h"
#include "Tools/Random.h"

void Game::ProcessEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape))
			window.close();

		if (Configuration::IsGameOver())
		{
			if (event.type == sf::Event::KeyPressed)
				Reset();
		}
		else if (Configuration::player != nullptr)
		{
			Configuration::player->ProcessNotRealTimeEvent(event);
		}
	}

	if (!Configuration::IsGameOver() && Configuration::player != nullptr)
		Configuration::player->ProcessEvents();
}

void Game::Update(float deltaTime)
{
	if (!Configuration::IsGameOver())
	{
		world.Update(deltaTime);

		if (Configuration::player == nullptr)
		{
			Configuration::player = new Player(world);
			Configuration::player->SetPosition(world.GetWidth() / 2, world.GetHeight() / 2);
			world.Add(Configuration::player);
		}

		timeUntilNextEnemySaucerAppears -= deltaTime;
		if (timeUntilNextEnemySaucerAppears < 0)
		{
			Saucer::CreateNewSaucer(world);
			timeUntilNextEnemySaucerAppears = Random::GenerateFloat(10.0f, 60.0f - Configuration::currentLevel * 2);
		}

		// If there only player ship is left
		if (world.GetExistingEntitiesCount() <= 1)
		{
			Configuration::currentLevel++;
			InitializeLevel();
		}
	}
}

void Game::Render()
{
	window.clear();

	if (Configuration::IsGameOver())
	{
		window.draw(textPromptForUser);
	}
	else
	{
		window.draw(world);
		Configuration::Draw(window);
	}

	window.display();
}

void Game::Reset()
{
	timeUntilNextEnemySaucerAppears = Random::GenerateFloat(5.0f, 6.0f - Configuration::currentLevel * 2);

	world.Clear();
	Configuration::player = nullptr;
	Configuration::Reset();

	InitializeLevel();
}

void Game::InitializeLevel()
{
	int bigMeteorsCount;

	switch (Configuration::currentLevel)
	{
	case 1:
		bigMeteorsCount = 4;
		break;
	case 2:
		bigMeteorsCount = 5;
		break;
	case 3:
		bigMeteorsCount = 7;
		break;
	case 4:
		bigMeteorsCount = 9;
		break;

	default:
		bigMeteorsCount = 10;
		break;
	}

	// Place all meteors of the world, with them not colliding with each other:
	for (int i = 0; i < bigMeteorsCount; i++)
	{
		Meteor* meteorPtr = new BigMeteor(world);

		do
		{
			meteorPtr->SetPosition(
				Random::GenerateFloat(0.0f, float(world.GetWidth())),
				Random::GenerateFloat(0.0f, float(world.GetHeight()))
			);

		} while (world.IsEntityCollideWithOthers(*meteorPtr));

		world.Add(meteorPtr);
	}
}

Game::Game()
	: windowSize(sf::VideoMode::getDesktopMode())
	, window(windowSize, WINDOW_TITLE, sf::Style::Fullscreen)
	, world(windowSize.width, windowSize.height)
{
	textPromptForUser.setFont(Configuration::fonts.Get(Configuration::Font::GUI));
	textPromptForUser.setCharacterSize(TEXT_RROMPT_FOR_USER_FONT_SIZE);
	textPromptForUser.setString("Press any key to start");

	sf::FloatRect textSize = textPromptForUser.getGlobalBounds();
	textPromptForUser.setOrigin(textSize.width / 2.0f, textSize.height / 2.0f);
	textPromptForUser.setPosition(windowSize.width / 2.0f, windowSize.height / 2.0f);
}

void Game::Run()
{
	sf::Clock deltaTime;

	while (window.isOpen())
	{
		ProcessEvents();
		Update(deltaTime.restart().asSeconds());
		Render();
	}
}