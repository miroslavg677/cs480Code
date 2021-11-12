#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
  // Initialize vectors that will be changed during runtime
  eyePosition = glm::vec3(0, 30.0, 41.0);
  focusPoint = glm::vec3(0.0, 0.0, 0.0);

 
  view = glm::lookAt( eyePosition, focusPoint, glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 100.0f); //Distance to the far plane, 
  return true;
}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}

void Camera::Rotate(float scalar) {

	if ((eyePosition.z > 1.0 && scalar > 0.0) || (eyePosition.z < 41.0 && scalar < 0.0))
		eyePosition += (glm::vec3(0.0, 1.0, -2.0) * scalar);

	view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
}


bool Camera::ZoomOut()
{
  eyePosition += glm::vec3(0.0, 0.0, 1.0);

  view = glm::lookAt( eyePosition, 
                      focusPoint, 
                      glm::vec3(0.0, 1.0, 0.0)); 

  return true;
}
