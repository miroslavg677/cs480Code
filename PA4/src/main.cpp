#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  std::string VertexFileName;
  std::string FragFileName;
  std::string MeshFileName;

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);

  //Check for command line arguments
  if (argc > 1)
  {
    std::string temp(argv[1]);
    FragFileName = temp;
    std::string temp1(argv[2]);
    VertexFileName = temp1;
    std::string temp2(argv[3]);
    MeshFileName = temp2;
  }
  
  else
  {
    //Message for the user if no command line arguments are entered
    std::cerr << "To run this program use the following command:" << std::endl;
    std::cerr << "----------------------------------------------" << std::endl;
    std::cerr << "./Tutorial frag.glsl vert.glsl table.obj" << std::endl;
    std::cerr << "grag.glsl is the current Fragmentation Shader" << std::endl;
    std::cerr << "vert.glsl is the current Vertex Shader" << std::endl;
    std::cerr << "table.obj is the current Mesh file " << std::endl;
    std::cerr << "----------------------------------------------" << std::endl;
  }
  //pass the command line arguments down the line
  if(!engine->Initialize(FragFileName, VertexFileName, MeshFileName))
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
