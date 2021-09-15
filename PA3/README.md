PA3 
By Miroslav Georgiev
CS 480 
9/14/2021

The shaders have been moved into the Shaders folder
The program will look for the shaders there

Compilation commands used:

mkdir build
cd build
cmake ..
make
./Tutorial

To Run the program:
./Tutorial frag.glsl vert.glsl
If the command line arguments are not included the program will print instructions on how to 
run the program

Functionality: 
A second cube(the moon) has been added to the program, it will orbit the first cube(the planet)
the user can still reverse the rotation of the planet as well as scaling the moon up or down as desired.

Pressing the R button will cause the planet to reverse it's rotation direction.
Pressing the left mouse button will also cause the planet to reverse it's rotation
pressing the left arrow key will set the orbit of the planet to the left
pressing the right arrow key will set the orbit of the planet to the right

Pressing the F button will cause the cube to stop orbiting but it will continue to spin about it's own y axis

pressing or holding the z key will cause the moon to get bigger
pressing or holding the x key will cause the moon to get smaller
