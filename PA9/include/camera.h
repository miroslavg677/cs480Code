#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();

    bool ZoomIn();
    bool ZoomOut();
    bool CameraLeft();
    bool CameraRight();
  
  private:
    glm::vec3 eyePosition;
    glm::vec3 focusPoint;

    glm::mat4 projection;
    glm::mat4 view;
};

#endif /* CAMERA_H */
