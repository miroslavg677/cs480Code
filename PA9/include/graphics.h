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
    void PlungerFire();

	void setAmbient();
	void setSpecular(int);
	void setSLSize(bool);
	void setSLBrightness(bool);

	//shader update
	void cycleShader();
	SpotLight sl;

  private:
    //lighting stuff
	glm::vec4 ambient;
	glm::vec4 incomingLight;

    std::string ErrorString(GLenum error);

	//Interaction stuff
	bool ambToggle = true;
	bool specBools[4] = {true};
	
	bool slSizeToggle = true;
	int slBrightToggle = true;

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

