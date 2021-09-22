
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

bool Engine::Initialize(std::string VertexName_E, std::string FragName_E, std::string MeshName_E) 
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
  //pass the command line arguments down the line
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, VertexName_E, FragName_E, MeshName_E))
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

    // Check the keyboard input
    
    
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();
    }
    

   
    // Update and render the graphics
    m_graphics->Update(m_DT, reverse, paused); // pass the references down to graphics
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
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }

    //Handle R being pressed makes the cube reverse direction
    if (m_event.key.keysym.sym == SDLK_r) 
    {
      reverse = !reverse;
    }

    //Handle F being pressed makes the cube stop orbiting but it still spins on it's y axis
    if (m_event.key.keysym.sym == SDLK_f)
    {
      paused = !paused;
    }
  }

  // Mouse section
  if (m_event.type == SDL_MOUSEBUTTONDOWN)
  {

    //Handles the left mouse click 
    //Makes the cube reverse direction same as R
    if(m_event.button.state == SDL_BUTTON_LEFT)
    {
      reverse = !reverse;
      std::cerr << "Left Mouse Button Pressed" << std::endl;
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
