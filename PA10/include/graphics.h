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
    void Rotate(float);
    PhysicsEngine physicsEngine;
    void PlungerFire();
    void LeftBumper();
    void RightBumper();

	void setAmbient(int);
	void setSpecular(bool);
	void setSLSize(int);
	void setSLBrightness(int);
	void ZoomOut();

	//shader update
	void cycleShader();
	SpotLight sl;

  private:
    //lighting stuff
	glm::vec4 ambient;
	glm::vec4 incomingLight;

    std::string ErrorString(GLenum error);

	//Interaction stuff
	bool specToggle = false;

    Camera *m_camera;
    Shader *m_shader[2];
	unsigned int shaderIndex = 0;
	bool shaderType = true;		// true = Gouraud, false = Phong

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

	GLint m_light;
	GLint m_ambient;
	GLint m_diffuse;
	GLint m_specular;
	GLint m_shininess;

	GLint m_spotLight;
	GLint m_sAmbient;
	GLint m_lightDir;
	GLint m_clipCosine;

    bool moveObjects;
};

#endif /* GRAPHICS_H */

