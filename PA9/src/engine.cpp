#include "engine.h"

Engine::Engine(string name, int width, int height)
{
	m_WINDOW_NAME = name;
	m_WINDOW_WIDTH = width;
	m_WINDOW_HEIGHT = height;
	m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
	m_WINDOW_NAME = name;
	m_WINDOW_HEIGHT = 0;
	m_WINDOW_WIDTH = 0;
	m_FULLSCREEN = true;
}

Engine::~Engine()
{
	delete m_window;
	delete m_graphics;
	m_window = NULL;
	m_graphics = NULL;
}

bool Engine::Initialize()
{
	// Start a window
	m_window = new Window();
	if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
	{
		printf("The window failed to initialize.\n");
		return false;
	}

	// Start the graphics
	m_graphics = new Graphics();
	if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
	{
		printf("The graphics failed to initialize.\n");
		return false;
	}


	// Set the time
	m_currentTimeMillis = GetCurrentTimeMillis();

	// No errors
	return true;
}

void Engine::Run()
{
	m_running = true;

	while(m_running)
	{
		// Update the DT
		m_DT = getDT();

		// Check keyboard input and mouse events
		while(SDL_PollEvent(&m_event) != 0)
		{
			Keyboard();
		}

		// Update and render the graphics
		m_graphics->Update(m_DT, Fire);
		m_graphics->Render();

		// Swap to the Window
		m_window->Swap();
	}
}

void Engine::Keyboard()
{
	if(m_event.type == SDL_QUIT)
	{
		m_running = false;
	}
	else if (m_event.type == SDL_KEYDOWN)
	{
		//Handle camera movement
		if(m_event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_running = false;
		}
		else if(m_event.key.keysym.sym == SDLK_s)
		{
			m_graphics->ZoomOut();
		}

		else if(m_event.key.keysym.sym == SDLK_w)
		{
			m_graphics->ZoomIn();
		}

		else if(m_event.key.keysym.sym == SDLK_a)
		{
			m_graphics->CameraLeft();
		}

		else if(m_event.key.keysym.sym == SDLK_d)
		{
			
			 m_graphics->CameraRight();
		}
			//Ambient Light Toggle
		else if(m_event.key.keysym.sym == SDLK_t) {
			m_graphics->setAmbient();
		}
		//Handle firing with keyboard
		else if(m_event.key.keysym.sym == SDLK_f)
		{
			//fire=!Fire; 
		}
			//Object Specular Lighting
		else if(m_event.key.keysym.sym == SDLK_1) {
			m_graphics->setSpecular(1);
		}
		else if(m_event.key.keysym.sym == SDLK_2) {
			m_graphics->setSpecular(2);
		}
		else if(m_event.key.keysym.sym == SDLK_3) {
			m_graphics->setSpecular(3);
		}
		else if(m_event.key.keysym.sym == SDLK_SPACE) {
		if (m_graphics != NULL)
			m_graphics->cycleShader();
		}
			//Spotlight Control
		else if(m_event.key.keysym.sym == SDLK_UP) {
			m_graphics->setSLSize(true);
		}
		else if(m_event.key.keysym.sym == SDLK_DOWN) {
			m_graphics->setSLSize(false);
		}
		else if(m_event.key.keysym.sym == SDLK_LEFT) {
			m_graphics->setSLBrightness(true);
		}
		else if(m_event.key.keysym.sym == SDLK_RIGHT) {
			m_graphics->setSLBrightness(false);
		}
	}

	else if(m_event.type == SDL_KEYUP)
	{
		if(m_event.key.keysym.sym ==SDLK_f)
		{
			//Fire=!Fire;
		}
	}
	//Handle firing with mouse
	if(m_event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(m_event.button.button == SDL_BUTTON_LEFT)
		{
			Fire =!Fire;
		}
	}
	else if( m_event.type == SDL_MOUSEBUTTONUP)
	{
		if(m_event.button.button == SDL_BUTTON_LEFT)
		{
			Fire =!Fire;
		}
	}
}

unsigned int Engine::getDT()
{
	long long TimeNowMillis = GetCurrentTimeMillis();
	assert(TimeNowMillis >= m_currentTimeMillis);
	unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
	m_currentTimeMillis = TimeNowMillis;
	return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
	timeval t;
	gettimeofday(&t, NULL);
	long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
	return ret;
}

