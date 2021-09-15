#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include <sys/time.h>
#include <assert.h>
#include "window.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, bool &reverse, bool &paused, glm::mat4 PosReferece, std::string Type, bool &MoonScaleUp, bool &MoonScaleDown);
    void Render();
    void Keyboard();

    glm::mat4 GetModel();
    glm::mat4 ModelRef;

  private:
    glm::mat4 model;
    glm::mat4 location;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    
    
    glm::vec3 position;

    float scaleammount = 0.75f; // used for scaling
    float angle;
    float angle2;   // Used to pause the cube
    float moon_angle; // How fast the moon orbits
    bool waspaused; // Used to pause the cube

    glm::mat4 perentRef; // Referece to the perent object's model matrix
    std::string ObjectType; // Planet or Moon
};

#endif /* OBJECT_H */
