#include "Window.h"
#include "Graphic.h"
#include "XmlSettings.h"
#include <memory>

using namespace DavinciEngine;

Window* Window::m_pWindow = nullptr;

Window::Window(const std::string &title,int width, int height, int bpp, bool fullscreen):
m_sTitle(title),m_iWidth(width),m_iHeight(height),m_iBpp(bpp),m_bFullscreen(fullscreen),m_iFlags(SDL_WINDOW_OPENGL)
,m_pScreen(nullptr),m_GLContext(nullptr)
{
}

Window::~Window()
{
}

void Window::Destroy()
{
	// Delete the window object
	delete m_pWindow;
	SDL_Quit();
}

Window *Window::NewWindow(const std::string &title, int width, int height, int bpp, bool fullscreen)
{
	if (!m_pWindow) {
		m_pWindow = new Window(title, width, height, bpp, fullscreen);

		if (!m_pWindow->SDLInit()) {
			delete m_pWindow;
			return nullptr;
		}
		if (!m_pWindow->OGLInit()) {
			delete m_pWindow;
			return nullptr;
		}
	}
	
	return m_pWindow;
}

Window* Window::GetInstance()
{
	if (!m_pWindow) {
		return nullptr;
	}
	return m_pWindow;
}

bool Window::SDLInit(){
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) 
	{		
		Error("SDL could not be intialized! SDL Error: %s", SDL_GetError());
		return false;
	}

	// All values are "at least"!	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (m_bFullscreen)
	{
		m_iFlags |= SDL_WINDOW_FULLSCREEN;
	}

	// Create the window
	m_pScreen = SDL_CreateWindow( m_sTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_iWidth, m_iHeight, m_iFlags );

	if (m_pScreen == nullptr)
	{
		Error("Window could not be created! SDL Error: %s", SDL_GetError());
		return false;
	}

	// Create the SDL OpenGL Context
	m_GLContext = SDL_GL_CreateContext(m_pScreen);

	if (m_GLContext == nullptr)
	{
		Error("OpenGL context could not be created! SDL Error: %s", SDL_GetError());
		return false;
	}

	// Activate Vsync - Will probably make this a menu setting later.
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		Warning("Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	// Enable the mouse cursor
	SDL_ShowCursor(SDL_ENABLE);

	return true;
}

bool Window::OGLInit(){

	GLenum glewError = GL_NO_ERROR;

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		// GLEW failed!
		Error("GLEW failed to initialize! Error: %s", glewGetErrorString(glewError));
		return false;
	}

	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);
	//glShadeModel(GL_SMOOTH);	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glDisable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLint viewPort[4];
	glGetIntegerv(GL_VIEWPORT, viewPort);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0.0f, m_iWidth, m_iHeight, 0.0f, -1.0f, 1.0f);
	glOrtho(0.0f, m_iWidth, 0.0f, m_iHeight, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glScalef(1.0, -1.0, 1.0);

	// Set the resolution scale for the current window
	SetWindowScale(Vec2D::one);

	// Set the window center coordinates for the current window
	SetWindowCenter(Vec2D(static_cast<float>(m_iWidth) / 2.0f, static_cast<float>(m_iHeight) / 2.0f));
	
	return true;
}

void Window::SetWindowCenter(const Vec2D center)
{
	m_vec2WindowCenter = center;
}

void Window::SetWindowScale(const Vec2D scale)
{
	m_vec2ResolutionScale = scale;
}

void Window::SetSize(int width, int height, bool fullscreen)
{	
	m_iHeight = height;
	m_iWidth = width;
	m_bFullscreen = fullscreen;

	SDLInit();
	OGLInit();

	XmlSettings::GetInstance()->SetWidth(m_iWidth);
	XmlSettings::GetInstance()->SetHeight(m_iHeight);
	XmlSettings::GetInstance()->SetBPP(m_iBpp);
	XmlSettings::GetInstance()->SetFullscreen(m_bFullscreen);
	XmlSettings::GetInstance()->SaveSettings();
}