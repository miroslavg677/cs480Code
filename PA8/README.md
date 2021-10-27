# PA8: Physics

For this project, we're demonstrating the bullet physics engine.

## Group Project
The members of our group are:\
John Busse\
Miroslav Georgiev\
Ryan Rytel

### Descripion
The project spawns a cube, a sphere(ball), a plane(board), a cylinder and a wall behind the ball when the user clicks the left mouse button the cube moves forward, hits the ball and makes it bounce off the cylinder. This is all done through Bullet. The ball is currently restricted to move only in the X-Y plane so it can't fall. This makes the bounce a lot better and it avoids a bug where the ball gets stuck in the wall behind it.

### Contr

  W:                 Zoom In Camera
  A:                 Turn Camera Left
  S:                 Zoom Out Camera
  D:                 Turn Camera Right
  Left Mouse Click:  fire ball
  ESC:               Close Program

### Building and running the program:

```bash
mkdir build
cd build
cmake ..
make
./PA8
```


