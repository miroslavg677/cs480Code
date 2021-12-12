# PA11: Final Project (Doomed Crusade)

A simple first person shooter game, mechanically inspired by the original Doom, and thematically inspired by the Warhammer 40K world

## Group Project
The members of our group are:\
John Busse\
Miroslav Georgiev\
Ryan Rytel\

### Descripion
```
	-A First Person Shooter like the original Doom
Progress Report Goals:
	-Player Movement:	Player can move forward, backward, strafe, and rotate
	-Working Physics:	Bullets & Player bounce off walls
	-Gun Firing:		Fire button launches a cube in the player facing direction
	-Lighting:
	-Whole level set up(3 rooms with coridors connecting them
	-Player looses health when they collide with enemies
	-Player gains score when they kill enemies
	-Button for changing the ambient lighting
	
```

### Controls
	W/S				Forward/Backward movement
	A/D				Stafe Left/Strafe Right
	Q/E				Turn Left/Turn Right
	Spacebar		Fire Weapon (Damages Enemies/Interacts with objects)

	ESC:			Close Program

### Requirements
Built in OpenGL 3.3\
Assimp				-Model loading\
GraphicsMagic++		-Texture loading\
Bullet				-Physics\
GLFW				-Windowing

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary.

```bash
mkdir build
cd build
cmake ..
make
./PA11
```


