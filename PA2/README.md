PA1 
By Miroslav Georgiev
CS 480 
9/7/2021

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

Pressing the R button will cause the cube to reverse it's rotation direction.
Pressing the left mouse button will also cause the cube to reverse it's rotation

Pressing the F button will cause the cube to stop orbiting but it will continue to spin about it's own y axis
