#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "physics.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt, bool& Fire);
    void Render();

    // for updating the view
    bool ZoomIn();
    bool ZoomOut();
    bool CameraLeft();
    bool CameraRight();
    PhysicsEngine physicsEngine;
    bool moveCube();
    bool PlungerFire();

  private:
    

    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    bool moveObjects;

    vector<Object *> masterList;

   
};

#endif /* GRAPHICS_H */

