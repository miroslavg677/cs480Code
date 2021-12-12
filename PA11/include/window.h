#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
//#include <GLFW/glfw3.h>

#include "graphics_headers.h"

#include <string>
using namespace std;

class Window
{
  public:
    Window();
    ~Window();
    bool Initialize(const string &name, int* width, int* height);
	void Swap();
	GLFWwindow* getWindow();

  private:
	GLFWwindow* window;
};

#endif 
