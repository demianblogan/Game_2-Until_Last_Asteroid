#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Actions/ActionMap.h"
#include "Tools/ResourceManager.h"

class Player;

// Configuration is a static class that contains all names of textures, fonts, sounds and music.
// Also it contains all possible actions that player can do, player's life, and stuff related to
// the game score. Don't forget to call "Initialize" method before the game starts!
class Configuration
{
public:
	enum class Texture
	{
		PlayerShip,
		PlayerLife,

		BigEnemySaucer,
		SmallEnemySaucer,

		BigMeteor1,
		BigMeteor2,
		BigMeteor3,
		BigMeteor4,

		MediumMeteor1,
		MediumMeteor2,

		SmallMeteor1,
		SmallMeteor2,
		SmallMeteor3,
		SmallMeteor4,

		PlayerShot,
		EnemySaucerShot
	};

	enum class Font
	{
		GUI // Graphical User Interface
	};

	enum class Sound
	{
		PlayerLaserShot,
		EmenyLaserShot,

		SaucerSpawn1,
		SaucerSpawn2,

		PlayerShipExplosion,
		Boom2,

		SmallMeteorExplosion,
		MediumMeteorExplosion,
		BigMeteorExplosion,

		HyperJump
	};

	enum class Music
	{
		BackgroundTheme
	};

	enum class PlayerAction
	{
		Up,
		Left,
		Right,
		Shoot,
		JumpToHyperspace
	};

	static ResourceManager<sf::Texture, Texture> textures;
	static ResourceManager<sf::Font, Font> fonts;
	static ResourceManager<sf::SoundBuffer, Sound> sounds;
	static ResourceManager<sf::Music, Music> music;

	static ActionMap<PlayerAction> playerActions;

	static Player* player;
	static int playerLives;
	static int currentLevel;

	Configuration() = delete;

	static void Initialize();
	static void Reset();
	static bool IsGameOver();
	static void AddScore(int points);
	static int GetScore();
	static void Draw(sf::RenderTarget& target);

private:
	static int score;
	static sf::Text textScore;
	static constexpr int SCORE_FONT_SIZE = 50;
	static constexpr int POINTS_NEEDED_FOR_EXTRA_LIFE = 1'000;

	static sf::Sprite spriteLife;
	static const sf::Vector2f SPRITE_LIFE_POSITION;

	static void InitializeTextures();
	static void InitializeFonts();
	static void InitializeSounds();
	static void InitializeMusics();
	static void InitializePlayerActions();
};