#include "DavinciImports.h"
#include "Game.h"

using namespace DavinciEngine;

int main()
{
	// Try to initialize the application...
	if(dengine()->Engine_Init())
	{
		// If all is well we run it!
		Game::GetInstance()->Run();
	}

	// If we can't initialize, or the application has quit we delete the instance and clean up.
	dengine()->Engine_Destroy();

	return 0;
};