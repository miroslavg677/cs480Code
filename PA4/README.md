PA4 
By Miroslav Georgiev
CS 480 
9/21/2021
Based on PA2

This program adds a obj file loader built into object.cpp
it supports obj file with UVs and Normals as well as obj files with no Normals or UVs
it will not support obj file with only Normals or only UVs baked in
The obj files are stored in the Meshes folder the program will look for them there
The color of the mesh is hard coded as orange

Compilation commands used:

mkdir build
cd build
cmake ..
make

To Run the program:
./Tutorial frag.glsl vert.glsl table.obj
or
./Tutorial frag.glsl vert.glsl table2.obj
table.obj and table2.obj are the same object but table.obj has UVs and Normals 
while table2.obj has no UVs or Normals
to load another obj file place the desired file in the Meshes folder and replace table.obj with the desired file's name.

If the command line arguments are not included the program will print instructions on how to 
run the program

Functionality: 

Pressing the R button will cause the cube to reverse it's rotation direction.
Pressing the left mouse button will also cause the cube to reverse it's rotation
Pressing the F button will cause the cube to stop orbiting but it will continue to spin about it's own y axis
