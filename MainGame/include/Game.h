#ifndef WITCHDOCTOR_H
#define WITCHDOCTOR_H

#define dengine Davinci::Engine_GetInstance

#include "DavinciImports.h"

class Game
{
public:
	static Game *GetInstance();
	static void Run();
private:
	Game( void ){};
	~Game( void ){};
	bool LoadMainMenu();
	static Game *m_WitchDoctor;
	bool m_menuLoaded;
};
#endif