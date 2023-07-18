#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "Vec2D.h"
//#include "CommandConsole.h"
#include "sdl/sdl.h"
#include <string>
#include <fstream>

namespace DavinciEngine{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Values that represent KeyCodes. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	enum KeyCode{
		KEY_UNDEFINED=-1,
		KEY_BACKSPACE=0,
		KEY_TAB,
		KEY_CLEAR,
		KEY_RETURN,
		KEY_PAUSE,
		KEY_ESCAPE,
		KEY_SPACE,
		KEY_QUOTE,
		KEY_COMMA,
		KEY_MINUS,
		KEY_PERIOD,
		KEY_SLASH,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_SEMICOLON,
		KEY_EQUALS,
		KEY_LEFTBRACKET,
		KEY_BACKSLASH,
		KEY_LESS,
		KEY_RIGHTBRACKET,
		KEY_BACKQUOTE,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_DELETE,
		KEY_KP0,
		KEY_KP1,
		KEY_KP2,
		KEY_KP3,
		KEY_KP4,
		KEY_KP5,
		KEY_KP6,
		KEY_KP7,
		KEY_KP8,
		KEY_KP9,
		KEY_KP_PERIOD,
		KEY_KP_DIVIDE,
		KEY_KP_MULTIPLY,
		KEY_KP_MINUS,
		KEY_KP_PLUS,
		KEY_UP,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_INSERT,
		KEY_HOME,
		KEY_END,
		KEY_PAGEUP,
		KEY_PAGEDOWN,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_F13,
		KEY_F14,
		KEY_F15,
		KEY_NUMLOCK,
		KEY_CAPSLOCK,
		KEY_SCROLLOCK,
		KEY_RSHIFT,
		KEY_LSHIFT,
		KEY_RCTRL,
		KEY_LCTRL,
		KEY_RALT,
		KEY_LALT,
		KEY_RMETA,
		KEY_LMETA,
		KEY_HELP,
		KEY_PRINT,
		KEY_BREAK,
		KEY_MENU,
		KEY_MAX = 323
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Values that represent mouse buttons. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	enum MouseButton
	{
		MOUSE_BUTTON_UNDEFINED=-1,
		MOUSE_BUTTON_LEFT=0,
		MOUSE_BUTTON_MIDDLE,
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_WHEELUP,
		MOUSE_BUTTON_WHEELDOWN,
		MOUSE_BUTTON_MAX
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Framework class sets up the engine to run on a certain type of platform. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Framework{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the instance.</summary>
		///
		/// <returns> null if it fails, else the instance.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Framework *GetInstance();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Destroys this object.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static void Destroy();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Updates this object.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Update();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the default content path.</summary>
		///
		/// <returns> The default content path.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const char * GetDefaultContentPath() noexcept {return "../";};

		/// <summary> Array holding boolean values for the KeyCode keys </summary>
		bool m_bKeys[KEY_MAX];

		/// <summary> Array holding boolean values for the mouse buttons </summary>
		bool m_bMouseButtons[MOUSE_BUTTON_MAX];

		/// <summary> The mouse coordinates </summary>
		Vec2D m_v2dMousePosition;

		/// <summary> The value of the mouse wheel </summary>
		float m_fMouseWheel;

	private:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Framework();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Destructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		~Framework();

		/// <summary> The pointer to the framework singleton </summary>
		static Framework *m_pFramework;
		//cCommandConsole *m_pCommandConsole;

		/// <summary> The width and height of the display </summary>
		int width,height;
	};
};
#endif