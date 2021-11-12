# PA10: Pinball

We're playing pinball

## Group Project
The members of our group are:\
John Busse\
Miroslav Georgiev\
Ryan Rytel\

### Descripion
```
-The objectie of this project is to build an interactive Pinball Game
-Use Assimp to load models and textures
-Use Bullet to handle the physics
```

### Controls
	C/M					Trigger left/right bumper
	Left Mouse				Launch ball (Intensity modified by how long you hold it)

	Up/Down Arrow		Rotate camera up/down

	R/F					Adjust radius of spotlight over ball up/down
	I/K					Adjust intensity of spotlight over ball up/down
	Q/A					Adjust ambient light up/down
	W/S					Toggle specularity high/low
	P					Toggle between Gouraud(per-vertex) and Phong(per-fragment) shading

	ESC:				Close Program

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary.

```bash
mkdir build
cd build
cmake ..
make
./PA10
```

### Makefile Instructions 
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./PA10
```
