# PA9: Lighting

The purpose of this assignment is to create multiple shaders to do per-vertex lighting and per-fragment ligting

## Group Project
The members of our group are:\
John Busse\
Miroslav Georgiev\
Ryan Rytel\\

### Descripion
```
-Building on PA8, add per-vertex lighting and per-fragment lighting. Make the shaders swappable on a keystroke
-Add a spotlight that can follow the sphere around as the sphere moves
-Have the ability to adjust parameters of lighting
--Ambient brightness
--Specular brightness of specific objects
--Spotlight size and brightness
```
### Concerns
```
-Miroslav and myself use VMWare as our Linux boxes, and it doesn't support OpenGL 4.3
-We had to dig around to find a set of Gouraud and Phong shaders that could work on 3.3
```
### Controls
	W/S:				Zoom Camera In/Out
	A/D:				Turn Camera Left/Right
	T:					Ambient brightness toggle
	Left Mouse Click:	fire ball
	Space:				Toggle per-vertex and per-fragment lighting
	1-3:				Toggle specularity of Cube, Sphere, and Cylinder (in that order)
	Up/Down Arrow:		Toggle spotlight size
	Left/Right Arrow:	Toggle spotlight brightness
	ESC:				Close Program

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary.

```bash
mkdir build
cd build
cmake ..
make
./PA9
```

### Makefile Instructions 
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./PA9
```
