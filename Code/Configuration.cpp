#include "Configuration.h"

#include "Tools/Random.h"

ResourceManager<sf::Texture, Configuration::Texture> Configuration::textures;
ResourceManager<sf::Font, Configuration::Font> Configuration::fonts;
ResourceManager<sf::SoundBuffer, Configuration::Sound> Configuration::sounds;
ResourceManager<sf::Music, Configuration::Music> Configuration::music;

ActionMap<Configuration::PlayerAction> Configuration::playerActions;

Player* Configuration::player = nullptr;
int Configuration::playerLives = -1;

int Configuration::currentLevel = -1;

int Configuration::score = -1;
sf::Text Configuration::textScore;

sf::Sprite Configuration::spriteLife;
const sf::Vector2f Configuration::SPRITE_LIFE_POSITION(80, 60);

void Configuration::Initialize()
{
	InitializeTextures();
	InitializeFonts();
	InitializeSounds();
	InitializeMusics();
	InitializePlayerActions();

	textScore.setFont(fonts.Get(Font::GUI));
	textScore.setCharacterSize(SCORE_FONT_SIZE);

	spriteLife.setTexture(textures.Get(Texture::PlayerLife));
	spriteLife.setScale(2.0f, 2.0f);

	// Start background music when game starts:
	sf::Music& backgroundMusic = music.Get(Music::BackgroundTheme);
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
}

void Configuration::Reset()
{
	currentLevel = 1;
	playerLives = 3;

	score = 0;
	textScore.setString("0");
}

bool Configuration::IsGameOver()
{
	return playerLives < 0;
}

void Configuration::AddScore(int points)
{
	// Every next level add new multiplier to added points. For example
	// if you add 500 points on 1st level, then its multiplier is 1.
	// If it's 2nd level, multiplier is 2, and you'll get 1000 points.

	// Also every time player has earned new POINTS_NEEDED_FOR_EXTRA_LIFE points
	// he gets +1 life.

	int oldScore = score;
	score += points * currentLevel;
	playerLives += score / POINTS_NEEDED_FOR_EXTRA_LIFE - oldScore / POINTS_NEEDED_FOR_EXTRA_LIFE;

	textScore.setString(std::to_string(score));
}

int Configuration::GetScore()
{
	return score;
}

void Configuration::Draw(sf::RenderTarget& target)
{
	target.draw(textScore);

	for (int life = 0; life < playerLives; life++)
	{
		spriteLife.setPosition(SPRITE_LIFE_POSITION.x * life, SPRITE_LIFE_POSITION.y);
		target.draw(spriteLife);
	}
}

void Configuration::InitializeTextures()
{
	// Load textures for player:
	textures.Load(Texture::PlayerShip, "Assets/Sprites/Player/Ship.png");
	textures.Load(Texture::PlayerLife, "Assets/Sprites/Player/Life.png");

	// Load textures for enemies:
	textures.Load(Texture::BigEnemySaucer, "Assets/Sprites/Enemies/BigEnemySaucer.png");
	textures.Load(Texture::SmallEnemySaucer, "Assets/Sprites/Enemies/SmallEnemySaucer.png");

	// Load textures for meteors:
	textures.Load(Texture::BigMeteor1, "Assets/Sprites/Meteors/BigMeteor1.png");
	textures.Load(Texture::BigMeteor2, "Assets/Sprites/Meteors/BigMeteor2.png");
	textures.Load(Texture::BigMeteor3, "Assets/Sprites/Meteors/BigMeteor3.png");
	textures.Load(Texture::BigMeteor4, "Assets/Sprites/Meteors/BigMeteor4.png");
	textures.Load(Texture::MediumMeteor1, "Assets/Sprites/Meteors/MediumMeteor1.png");
	textures.Load(Texture::MediumMeteor2, "Assets/Sprites/Meteors/MediumMeteor2.png");
	textures.Load(Texture::SmallMeteor1, "Assets/Sprites/Meteors/SmallMeteor1.png");
	textures.Load(Texture::SmallMeteor2, "Assets/Sprites/Meteors/SmallMeteor2.png");
	textures.Load(Texture::SmallMeteor3, "Assets/Sprites/Meteors/SmallMeteor3.png");
	textures.Load(Texture::SmallMeteor4, "Assets/Sprites/Meteors/SmallMeteor4.png");

	// Load textures for shots:
	textures.Load(Texture::PlayerShot, "Assets/Sprites/Shots/PlayerShot.png");
	textures.Load(Texture::EnemySaucerShot, "Assets/Sprites/Shots/EnemySaucerShot.png");
}

void Configuration::InitializeFonts()
{
	fonts.Load(Font::GUI, "Assets/Fonts/trs-million.ttf");
}

void Configuration::InitializeSounds()
{
	// Load sounds for shots:
	sounds.Load(Sound::PlayerLaserShot, "Assets/Sounds/PlayerLaserShot.ogg");
	sounds.Load(Sound::EnemyLaserShot, "Assets/Sounds/EnemyLaserShot.ogg");

	// Load sounds for enemies spawn:
	sounds.Load(Sound::SaucerKamikazeSpawn, "Assets/Sounds/SaucerKamikazeSpawn.flac");
	sounds.Load(Sound::SaucerShooterSpawn, "Assets/Sounds/SaucerShooterSpawn.flac");

	// Load sounds for booms:
	sounds.Load(Sound::PlayerShipExplosion, "Assets/Sounds/PlayerShipExplosion.flac");
	sounds.Load(Sound::EnemySaucerExplosion, "Assets/Sounds/EnemySaucerExplosion.flac");

	// Load sounds for explosions:
	sounds.Load(Sound::BigMeteorExplosion, "Assets/Sounds/BigMeteorExplosion.flac");
	sounds.Load(Sound::MediumMeteorExplosion, "Assets/Sounds/MediumMeteorExplosion.flac");
	sounds.Load(Sound::SmallMeteorExplosion, "Assets/Sounds/SmallMeteorExplosion.flac");

	// Load sounds for others:
	sounds.Load(Sound::HyperJump, "Assets/Sounds/HyperJump.flac");
}

void Configuration::InitializeMusics()
{
	music.Load(Music::BackgroundTheme, "Assets/Music/BackgroundTheme.ogg");
}

void Configuration::InitializePlayerActions()
{
	playerActions.Map(PlayerAction::Up, Action(sf::Keyboard::Up));
	playerActions.Map(PlayerAction::Left, Action(sf::Keyboard::Left));
	playerActions.Map(PlayerAction::Right, Action(sf::Keyboard::Right));
	playerActions.Map(PlayerAction::JumpToHyperspace, Action(sf::Keyboard::Down, Action::Type::Released));
	playerActions.Map(PlayerAction::Shoot, Action(sf::Keyboard::Space));
}