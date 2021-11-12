#include "engine.h"

int main(int argc, char **argv)
{
	
  Magick::InitializeMagick(*argv);
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("PA10: Pinball", 1920, 1080);
  cout	<< "Pinball Controls" << endl
			<< "Left Mouse	Launch Ball (Hold to increase intensity)" << endl
			<< "C/M		Toggle Left/Right Bumper" << endl
			<< "Up/Down		Rotate Camera Up/Down" << endl
			<< "R/F		Adjust Ball Spotlight Radius Up/Down" << endl
			<< "I/K		Adjust Ball Spotlight Intensity" << endl
			<< "Q/A		Adjust Ambient Light Up/Down" << endl
			<< "W/S		Toggle Specularity High/Low" << endl
			<< "P		Toggle per-vertex and per-fragment shading" << endl
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

