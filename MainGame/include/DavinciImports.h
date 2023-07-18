#ifndef DAVINCI_H
#define DAVINCI_H

#include <string>

namespace DavinciEngine{

	class __declspec(dllimport) Davinci
	{		
	public:

		// Game Engine Main Functions
		static Davinci *Engine_GetInstance ( void );
		void Engine_Destroy( void );
		bool Engine_Init();
		void Engine_Update();

		// Game Timer Functions
		void TimerStart();
		void TimerPause();
		float TimerGetTicks();

		// Game Mode Manager Functions
		int GetGameMode();
		void SetGameMode(int mode);

		// Game Script Engine
		bool RunScript(const char *scriptFile);

		// Game Graphics Functions
		void SetResolution(int windowWidth, int windowHeight);
		void SetFullscreen(bool fullscreen);
		bool IsFullscreen();
		int GetWindowWidth();
		int GetWindowHeight();

		// Game Logging Functions
		void Engine_Log(const char *message);
		void Engine_Warning(const char *warning);
		void Engine_Error(const char *error);
		void Engine_FatalError(const char *fatal_error);

		// Game Object Functions
		void ClearScene();
		bool LoadActor(const char *type, float xPos, float yPos);
		
	};
}
#endif