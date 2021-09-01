#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  std::string VertexFileName;
  std::string FragFileName;
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);

  //Check if there is a second argument
  //If so it's the file name for the shader
  if (argc > 1)
  {
    std::string temp(argv[1]);
    FragFileName = temp;
    std::string temp1(argv[2]);
    VertexFileName = temp1;
  }
  if(!engine->Initialize(FragFileName, VertexFileName))
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
