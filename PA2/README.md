PA1 
By Miroslav Georgiev
CS 480 
9/7/2021

Note the program expects the file path for the project to be the following:
/home/<Username>/cs480Georgiev/PA2/

if it something different it must be changed in shader.cpp line 49
since the username will be different it is nessessary to go in and change it

Compilation commands used:

mkdir build
cd build
cmake ..
make
./Tutorial

Functionality: 

Pressing the R button will cause the cube to reverse it's rotation direction.
Pressing the left mouse button will also cause the cube to reverse it's rotation

Pressing the F button will cause the cube to stop orbiting but it will continue to spin about it's own y axis
