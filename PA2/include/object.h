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
    void Update(unsigned int dt, bool &reverse, bool &paused);
    void Render();
    void Keyboard();

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    glm::mat4 location;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    
    
    glm::vec3 position;

    float angle;
    float angle2;   // Used to pause the cube
    bool waspaused; // Used to pause the cube
};

#endif /* OBJECT_H */
