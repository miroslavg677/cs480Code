# PA5: Assimp and Model Loading

For this project, we're using Assimp to load and display models.
This is an iteration from the previous project, so I'm starting with a copy of PA4

## Group Project
The members of our group are:
John Busse
Miroslav Georgiev
Ryan Rytel

### Descripion
This program uses Assimp to load a model into the program and then spins that model
so the user can see it from all angles.

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary.

```bash
mkdir build
cd build
cmake ..
make
./PA5 object.obj
```

### Makefile Instructions 
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./PA5 object.obj
```

## Running the program:
To run the program use the following command:
./PA5 object.obj
object.obj is the test model and has materials baked in
The program expects obj files to be in the models folder if they are placed elsewhere it will not load them
to load another obj file replace object.obj with the desired file name 
make sure the desired file is in the PA5/models folder
