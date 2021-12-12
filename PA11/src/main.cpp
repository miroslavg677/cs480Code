#include "engine.h"

int main(int argc, char **argv)
{
	
  Magick::InitializeMagick(*argv);
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("PA11: Doomed Crusade", 1280, 720);
  cout	<< "Controls" << endl
			<< "W/S		Move forward/backward" << endl
			<< "A/D		Strafe Left/Right" << endl
			<< "Q/E		Turn Left/Right" << endl
			<< "F		Flashlight" << endl
			<< "Spacebar	Fire" << endl
      << "ESC		Close Program" << endl
      << "Lives Remaining: 3" << endl;


  // Initialize the engine
  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }

  // Run the engine, and clean it up after
  engine->Run();

  delete engine;
  engine = NULL;
  return 0;
}

