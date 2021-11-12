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
	bool holdL = false, holdR = false;
	if(m_event.type == SDL_QUIT)
	{
		m_running = false;
	}
	else if (m_event.type == SDL_KEYDOWN)
	{
		if(m_event.key.keysym.sym == SDLK_ESCAPE) {
			//Quit Program
			m_running = false;
		}
		else if(m_event.key.keysym.sym == SDLK_c) {
			//Trigger left bumper
			if(holdL==false)
			{
				m_graphics->LeftBumper();
				holdL=true;
			}
		}
		else if(m_event.key.keysym.sym == SDLK_m) {
			//Trigger right bumper
			if(holdR==false)
			{
				m_graphics->RightBumper();
				holdR=true;
			}
		}
		else if(m_event.key.keysym.sym == SDLK_SPACE) {
			//Fire ball
			//Fire =!Fire;
		}
		else if(m_event.key.keysym.sym == SDLK_UP) {
			//rotate camera up
			m_graphics->Rotate(1.0);
		}
		else if(m_event.key.keysym.sym == SDLK_DOWN) {
			//rotate camera down
			m_graphics->Rotate(-1.0);
		}
		else if(m_event.key.keysym.sym == SDLK_r) {
			//Spotlight Radius Up
			m_graphics->setSLSize(-1);
		}
		else if(m_event.key.keysym.sym == SDLK_f) {
			//Spotlight Radius Down
			m_graphics->setSLSize(1);
		}
		else if(m_event.key.keysym.sym == SDLK_i) {
			//Spotlight Intensity Up
			m_graphics->setSLBrightness(1);
		}
		else if(m_event.key.keysym.sym == SDLK_k) {
			//Spotlight Intensity Down
			m_graphics->setSLBrightness(-1);
		}
		else if(m_event.key.keysym.sym == SDLK_q) {
			//Ambient Light Up
			m_graphics->setAmbient(1);
		}
		else if(m_event.key.keysym.sym == SDLK_a) {
			//Ambient Light Down
			m_graphics->setAmbient(-1);
		}
		else if(m_event.key.keysym.sym == SDLK_w) {
			//Toggle Specularity High
			m_graphics->setSpecular(true);
		}
		else if(m_event.key.keysym.sym == SDLK_s) {
			//Toggle Specularity Low
			m_graphics->setSpecular(false);
		}
		else if(m_event.key.keysym.sym == SDLK_p) {
			//Cycle Gouraud/Phong Shader
			if (m_graphics != NULL)
				m_graphics->cycleShader();
		}
		else if(m_event.key.keysym.sym == SDLK_z) {
			//Zoom camera out
				m_graphics->ZoomOut();
		}
	}
	if (m_event.type == SDL_KEYUP)
	{
		if(m_event.key.keysym.sym == SDLK_SPACE) 
		{
			//Fire ball
			//Fire =!Fire;
		}
		else if(m_event.key.keysym.sym == SDLK_c) {
			//Trigger left bumper
			m_graphics->LeftBumper();
			holdL=false;
		}
		else if(m_event.key.keysym.sym == SDLK_m) {
			//Trigger right bumper
			m_graphics->RightBumper();
			holdR=false;
		}
	}
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

