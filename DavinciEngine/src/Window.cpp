#include "Window.h"
#include "Graphic.h"
#include "XmlSettings.h"
#include "glad/gl.h"
#include <memory>

using namespace DavinciEngine;

Window* Window::m_pWindow = nullptr;

Window::Window(const std::string& title, int width, int height, int bpp, bool fullscreen) :
	m_sTitle(title), m_iWidth(width), m_iHeight(height), m_iBpp(bpp), m_bFullscreen(fullscreen)
{}

Window::~Window()
{}

void Window::Destroy()
{
	// Delete the window object
	delete m_pWindow;
	m_pWindow = nullptr;
	SDL_Quit();
}

Window* Window::NewWindow(const std::string& title, int width, int height, int bpp, bool fullscreen)
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

bool Window::SDLInit() {
	if (SDL_Init(SDL_INIT_VIDEO) == false)
	{
		Error("SDL could not be intialized! SDL Error: %s", SDL_GetError());
		return false;
	}

	// All values are "at least"!	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (m_bFullscreen)
	{
		m_iFlags |= SDL_WINDOW_FULLSCREEN;
	}

	// Create the window
	m_pScreen = SDL_CreateWindow(m_sTitle.c_str(), m_iWidth, m_iHeight, m_iFlags);

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
	if (SDL_GL_SetSwapInterval(1) == false)
	{
		Warning("Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	// Enable the mouse cursor
	SDL_ShowCursor();

	return true;
}

bool Window::OGLInit()
{
	// Initialize GLAD
	if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress))
	{
		Error("Failed to initialize GLAD");
		return false;
	}

	// Set viewport
	glViewport(0, 0, m_iWidth, m_iHeight);

	// Enable blending (still valid)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Optional: enable backface culling (modern way)
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Depth (disabled for 2D, fine for now)
	glDisable(GL_DEPTH_TEST);

	// Clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear once
	glClear(GL_COLOR_BUFFER_BIT);

	// Set the resolution scale for the current window
	SetWindowScale(glm::vec2(1.0f, 1.0f));

	// Set the window center coordinates for the current window
	SetWindowCenter(glm::vec2(static_cast<float>(m_iWidth) / 2.0f, static_cast<float>(m_iHeight) / 2.0f));

	return true;
}

void Window::SetWindowCenter(const glm::vec2 center)
{
	m_vec2WindowCenter = center;
}

void Window::SetWindowScale(const glm::vec2 scale)
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