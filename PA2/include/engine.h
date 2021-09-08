#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>

#include "graphics.h"
#include "window.h"
#include "string.h"

//Use to carry data down to where it is needed:
struct DataCarrier
{
  public:
  // Shaders
  std::string VertexShaderFileName_1;
  std::string FragShaderFileName_1;

  //Textures


  //Models
  //Add sections as needed...
};

class Engine
{
  public:
    Engine(string name, int width, int height);
    Engine(string name);
    ~Engine();
    bool Initialize(std::string VertexName_E, std::string FragName_E);
    void Run();
    void Keyboard();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
  
  private:
    // Window related variables
    Window *m_window;    
    string m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    SDL_Event m_event;

    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    bool m_running;
    bool paused;
    bool reverse;
};

#endif // ENGINE_H
