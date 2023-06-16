#include "Configuration.h"
#include "Game.h"

int main()
{
	Configuration::Initialize();
	Game().Run();

	return 0;
}