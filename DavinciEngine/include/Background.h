#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "TextureManager.h"
#include "ObjectManager.h"
#include <string>

namespace GameEngine{
	namespace EngineObjects{

		class Background : public MainObject
		{
		public:
			static bool New(float xPos, float yPos, float width, float height, char *texturePath);
		private:
			Background();
			~Background();
		};
	}
}
#endif