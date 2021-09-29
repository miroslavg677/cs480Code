#include <iostream>

#include "engine.h"

int main(int argc, char **argv)
{
  std::string MeshFileName;
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("PA4: Model Loading", 800, 600);

  if(argc > 1)
  {
    //Read in the command line argument(s) 
    std::string temp(argv[1]); // first one should be the file name of the mesh
    MeshFileName = temp;
  }

  else
  {
    //Message for the user if no command line arguments are entered
    std::cerr << "To run this program use the following command:" << std::endl;
    std::cerr << "----------------------------------------------" << std::endl;
    std::cerr << "./PA5 object.obj" << std::endl;
    std::cerr << "object.obj is the test obj file " << std::endl;
    std::cerr << "to load another file replace object.obj  " << std::endl;
    std::cerr << "with the name of the desired file " << std::endl;
    std::cerr << "file must be in the models folder " << std::endl;
    std::cerr << "----------------------------------------------" << std::endl;
  }

  if(!engine->Initialize(MeshFileName)) // pass down the Mesh Name
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
