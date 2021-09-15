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
  else
  {
    //Message for the user if no command line arguments are entered
    std::cerr << "To run this program use the following command:" << std::endl;
    std::cerr << "----------------------------------------------" << std::endl;
    std::cerr << "./Tutorial frag.glsl vert.glsl" << std::endl;
    std::cerr << "grag.glsl is the current Fragmentation Shader" << std::endl;
    std::cerr << "vert.glsl is the current Vertex Shader" << std::endl;
    std::cerr << "----------------------------------------------" << std::endl;
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
