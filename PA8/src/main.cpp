#include <cstdio>
#include <Magick++.h>
#include "engine.h"
#include "tinyxml2.h"

int main(int argc, char **argv)
{

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("PA8: Bullet", 800, 600);
  cout	<< "Camera Controls" << endl
			<< "W\t       Zoom In" << endl
			<< "A\t       Turn Camera Left" << endl
			<< "S\t       Zoom Out" << endl
			<< "D\t       Turn Camera Right" << endl
			<< "L Mouse Click  fire ball" << endl
      << "ESC\t       Close Program" << endl;
  Magick::InitializeMagick(*argv);

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

