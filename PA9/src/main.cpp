#include "engine.h"

int main(int argc, char **argv)
{
	
  Magick::InitializeMagick(*argv);
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("PA9: Lighting", 800, 600);
  cout	<< "Camera Controls" << endl
			<< "W			Zoom In" << endl
			<< "A			Turn Camera Left" << endl
			<< "S			Zoom Out" << endl
			<< "D			Turn Camera Right" << endl
			<< "L Mouse Click		fire ball" << endl
			<< "T			Toggle ambient light" << endl
			<< "1, 2, 3			toggle specularity of Cube, Ball, Cylinder (in that order)" << endl
			<< "Spacebar		toggle Gouraud/Phong shading" << endl
			<< "Up/Down Arrow		Increase/Decrease Spotlight Size" << endl
			<< "Left/Right Arrow	Increase/Decrease Spotlight Brightness" << endl
      << "ESC			Close Program" << endl;

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

