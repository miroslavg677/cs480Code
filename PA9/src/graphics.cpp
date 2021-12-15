#include "graphics.h"
extern bool input;
extern bool Fire;

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
	
}

bool Graphics::Initialize(int width, int height)
{
	// Used for the linux OS
	#if !defined(__APPLE__) && !defined(MACOSX)
		// cout << glewGetString(GLEW_VERSION) << endl;
		glewExperimental = GL_TRUE;

		auto status = glewInit();

		// This is here to grab the error that comes from glew init.
	// This error is an GL_INVALID_ENUM that has no effects on the performance
		glGetError();

		//Check for error
		if (status != GLEW_OK)
		{
			std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
			return false;
		}
	#endif

	// For OpenGL 3
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Init Camera
	m_camera = new Camera();
	if(!m_camera->Initialize(width, height))
	{
		printf("Camera Failed to Initialize\n");
		return false;
	}

	// Set up the shaders
	// Set up Gourand shader
	m_shader[0] = new Shader();
	if(!m_shader[0]->Initialize())
	{
		printf("Shader Failed to Initialize\n");
		return false;
	}

	// Add the vertex shader
	if(!m_shader[0]->AddShader(GL_VERTEX_SHADER, "shaders/pvVert.glsl"))
	{
		printf("Gouraud Vertex Shader failed to Initialize\n");
		return false;
	}

	// Add the fragment shader
	if(!m_shader[0]->AddShader(GL_FRAGMENT_SHADER, "shaders/pvFrag.glsl"))
	{
		printf("Gouraud Fragment Shader failed to Initialize\n");
		return false;
	}

	// Set up Phong shader
	m_shader[1] = new Shader();
	if(!m_shader[1]->Initialize())
	{
		printf("Shader Failed to Initialize\n");
		return false;
	}

	// Add the vertex shader
	if(!m_shader[1]->AddShader(GL_VERTEX_SHADER, "shaders/pfVert.glsl"))
	{
		printf("Phong Vertex Shader failed to Initialize\n");
		return false;
	}

	// Add the fragment shader
	if(!m_shader[1]->AddShader(GL_FRAGMENT_SHADER, "shaders/pfFrag.glsl"))
	{
		printf("Phong Fragment Shader failed to Initialize\n");
		return false;
	}

	physicsEngine.SetUpPhysics(); //Sets up the Bullet physics world that the simulation will run in

	// And now we create all the desired physics objects
	// The rendered objects are also created
	physicsEngine.CreatePlane();
	physicsEngine.CreateCube(btVector3(1,1,5), btVector3(1.0f, 1.0f, 1.0f), btScalar(0.0f));
	physicsEngine.CreateBall(btVector3(1,1,3), btScalar(1.0f), btScalar(0.8f));
	physicsEngine.CreateCylinder(btVector3(1.5,1,-5), btVector3(1.0f, 1.0f, 1.0f), btScalar(0.0f));
	physicsEngine.CreateWall(btVector3(1,1,10));

	//Set up lights

	incomingLight = {10.0, 100.0, 0.0, 1.0};
	ambient = {0.44, 0.44, 0.44, 1.0};

	sl.incoming = {0.0, -1.0, 0.0, 1.0};
	sl.ambient = {0.67, 0.80, 0.67, 1.0};
	sl.angle = glm::cos(glm::radians(5.0));

	// Connect the program
	if(!m_shader[0]->Finalize())
	{
		printf("Program to Finalize\n");
		return false;
	}

	if(!m_shader[1]->Finalize())
	{
		printf("Program to Finalize\n");
		return false;
	}

	m_spotLight = m_shader[0]->GetUniformLocation("lightPosition");
	if(m_spotLight == INVALID_UNIFORM_LOCATION) {
		cout << "light position not found\n";
	}

	m_sAmbient = m_shader[0]->GetUniformLocation("sAmbient");
	if(m_sAmbient == INVALID_UNIFORM_LOCATION) {
		cout << "ambient value not found\n";
	}

	 m_lightDir = m_shader[0]->GetUniformLocation("lightDir");
	if(m_lightDir == INVALID_UNIFORM_LOCATION)
	{
		printf("light direction not found\n");
	}

	m_clipCosine = m_shader[0]->GetUniformLocation("clip");
	if(m_clipCosine == INVALID_UNIFORM_LOCATION)
	{
		printf("clip not found\n");
	}

	m_diffuse = m_shader[0]->GetUniformLocation("DiffuseColor");
	if(m_diffuse == INVALID_UNIFORM_LOCATION)
	{
		printf("diffuse not found\n");
	}

	m_specular = m_shader[0]->GetUniformLocation("SpecularColor");
	if(m_specular == INVALID_UNIFORM_LOCATION)
	{
		printf("specular color not found\n");
	}

	m_shininess = m_shader[0]->GetUniformLocation("Shininess");
	if(m_shininess == INVALID_UNIFORM_LOCATION)
	{
		printf("shininess not found\n");
	}

	m_ambient = m_shader[0]->GetUniformLocation("AmbientColor");
	if(m_ambient == INVALID_UNIFORM_LOCATION)
	{
		printf("ambient color not found\n");
	}

	m_light = m_shader[0]->GetUniformLocation("LightArray");
	if(m_light == INVALID_UNIFORM_LOCATION)
	{
		printf("light array not found\n");
	}

	// Locate the projection matrix in the shader
	m_projectionMatrix = m_shader[0]->GetUniformLocation("projectionMatrix");
	if(m_projectionMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("projection matrix not found\n");
	}

	// Locate the view matrix in the shader
	m_viewMatrix = m_shader[0]->GetUniformLocation("viewMatrix");
	if(m_viewMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("view matrix not found\n");
	}

	// Locate the model matrix in the shader
	m_modelMatrix = m_shader[0]->GetUniformLocation("modelMatrix");
	if(m_modelMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("model matrix not found\n");
	}

	//enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// enable object movement
	moveObjects = true;

	return true;
}

void Graphics::Update(unsigned int dt, bool& Fire)
{
	physicsEngine.Update(dt);
	if(Fire == true)
	{
	 physicsEngine.PlungerFire();
	}
}

// Set ambient light; toggle between 1/2x value and 2x value
void Graphics::setAmbient() {
	cout << "Ambient light toggled ";
	//ambToggle starts as true, so if it initially gets flipped, we divide the number by 2
	ambToggle = !ambToggle;

	if(ambToggle) {
		cout << "up\n";
		ambient.r *= 2.0;
		ambient.b *= 2.0;
		ambient.g *= 2.0;
	}
	else {
		cout << "down\n";
		ambient.r *= 0.5;
		ambient.g *= 0.5;
		ambient.b *= 0.5;
	}
}

// set Specular light; toggle a value in a boolean array
void Graphics::setSpecular(int index){
	cout << "Object " << index << " specularity toggled" << endl;
	specBools[index] = !specBools[index];
}

// set spotlight size; change the spotlight's angle
void Graphics::setSLSize(bool toggle) {
	if(toggle && sl.angle < 1.0) {
		cout << "Spotlight Size decreased\n";
		sl.angle += 0.001;
	}
	else if(!toggle && sl.angle > 0.0) {
		cout << "Spotlight Size increased\n";
		sl.angle -= 0.001;
	}
}

// set Spotlight Brightness; change the spotlights alpha value
void Graphics::setSLBrightness(bool toggle) {
	if(toggle) {
		cout << "Spotlight brightness increased\n";
		sl.ambient.r += 0.1;
		sl.ambient.g += 0.1;
		sl.ambient.b += 0.1;
	}
	else if(!toggle) {
		cout << "Spotlight brightness decreased\n";
		sl.ambient.r -= 0.1;
		sl.ambient.g -= 0.1;
		sl.ambient.b -= 0.1;
	}
}

void Graphics::Render()
{
	glm::mat4 tempMat;
	glm::vec4 tempVec;
	int index;

	//clear the screen
	glClearColor(0.0, 0.0, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start the correct program
	m_shader[shaderIndex]->Enable();

	// Send in the projection and view to the shader
	glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
	glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));
	glUniform4f(m_ambient, ambient.r, ambient.g, ambient.b, ambient.a);
	glUniform4f(m_light, incomingLight.r, incomingLight.g, incomingLight.b, incomingLight.a);

	// Attach the spotlight to the sphere
	index = physicsEngine.getBallIndex();

	tempMat = physicsEngine.visibleObjects[index]->GetModel();

	tempVec = tempMat * glm::vec4(0.0, 0.0, 0.0, 1.0);

	glUniform4f(m_spotLight, tempVec.x, tempVec.y + 80.0, tempVec.z, 1.0);
	glUniform4f(m_sAmbient, sl.ambient.r, sl.ambient.g, sl.ambient.b, sl.ambient.a);
	glUniform3f(m_lightDir, sl.incoming.r, sl.incoming.g, sl.incoming.b);
	glUniform1f(m_clipCosine, sl.angle);

	//Go through the visible objects and update them
	for(int i = 0; i < physicsEngine.visibleObjects.size(); i++)
	{
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(physicsEngine.visibleObjects[i]->GetModel()));

		tempVec = physicsEngine.visibleObjects[i]->getDiffuse();

		glUniform4f(m_diffuse, tempVec.r, tempVec.g, tempVec.b, tempVec.a);

		tempVec = physicsEngine.visibleObjects[i]->getSpecular();
		if (specBools[i]) {
			tempVec.r *= 2.0;
			tempVec.g *= 2.0;
			tempVec.b *= 2.0;
		}
		else {
			tempVec.r *= 0.5;
			tempVec.g *= 0.5;
			tempVec.b *= 0.5;
		}

		glUniform4f(m_specular, tempVec.r, tempVec.g, tempVec.b, tempVec.a);

		glUniform1f(m_shininess, physicsEngine.visibleObjects[i]->getShine());

		physicsEngine.visibleObjects[i]->Render();
	}

	// Get any errors from OpenGL
	auto error = glGetError();
	if (error != GL_NO_ERROR)
	{
		string val = ErrorString(error);
		std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
	}
}

std::string Graphics::ErrorString(GLenum error)
{
	if(error == GL_INVALID_ENUM)
	{
		return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
	}

	else if(error == GL_INVALID_VALUE)
	{
		return "GL_INVALID_VALUE: A numeric argument is out of range.";
	}

	else if(error == GL_INVALID_OPERATION)
	{
		return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
	}

	else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
	{
		return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
	}

	else if(error == GL_OUT_OF_MEMORY)
	{
		return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
	}
	else
	{
		return "None";
	}
}

// Light/Shader functions
void Graphics::cycleShader() {
	shaderType = !shaderType;	//flip the boolean

	cout << "Switching to ";

	if (shaderType) {
		shaderIndex = 0;
		cout << "Gouraud/per-vertex";
	}
	else {
		shaderIndex = 1;
		cout << "Phong/per-fragment";
	}
	cout << " shading\n";

	m_spotLight = m_shader[shaderIndex]->GetUniformLocation("lightPosition");
	if(m_spotLight == INVALID_UNIFORM_LOCATION) {
		cout << "light position not found\n";
	}

	m_sAmbient = m_shader[shaderIndex]->GetUniformLocation("sAmbient");
	if(m_sAmbient == INVALID_UNIFORM_LOCATION) {
		cout << "sAmbient not found\n";
	}

	m_lightDir = m_shader[shaderIndex]->GetUniformLocation("lightDir");
	if(m_lightDir == INVALID_UNIFORM_LOCATION)
	{
		printf("Light Direction not found\n");
	}

	m_clipCosine = m_shader[shaderIndex]->GetUniformLocation("clip");
	if(m_clipCosine == INVALID_UNIFORM_LOCATION)
	{
		printf("clip not found\n");
	}

	m_diffuse = m_shader[shaderIndex]->GetUniformLocation("DiffuseColor");
	if(m_diffuse == INVALID_UNIFORM_LOCATION)
	{
		printf("Diffuse Color not found\n");
	}

	m_specular = m_shader[shaderIndex]->GetUniformLocation("SpecularColor");
	if(m_specular == INVALID_UNIFORM_LOCATION)
	{
		printf("Specular Color not found\n");
	}

	m_shininess = m_shader[shaderIndex]->GetUniformLocation("Shininess");
	if(m_shininess == INVALID_UNIFORM_LOCATION)
	{
		printf("Shininess not found\n");
	}

	m_ambient = m_shader[shaderIndex]->GetUniformLocation("AmbientColor");
	if(m_ambient == INVALID_UNIFORM_LOCATION)
	{
		printf("Ambient Color not found\n");
	}

	m_light = m_shader[shaderIndex]->GetUniformLocation("LightArray");
	if(m_light == INVALID_UNIFORM_LOCATION)
	{
		printf("Light Array not found\n");
	}

	// Locate the projection matrix in the shader
	m_projectionMatrix = m_shader[shaderIndex]->GetUniformLocation("projectionMatrix");
	if(m_projectionMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_projectionMatrix not found\n");
	}

	// Locate the view matrix in the shader
	m_viewMatrix = m_shader[shaderIndex]->GetUniformLocation("viewMatrix");
	if(m_viewMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_viewMatrix not found\n");
	}

	// Locate the model matrix in the shader
	m_modelMatrix = m_shader[shaderIndex]->GetUniformLocation("modelMatrix");
	if(m_modelMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_modelMatrix not found\n");
	}	
}	

//Camera functions
bool Graphics::ZoomIn()
{
	return m_camera->ZoomIn();
}

bool Graphics::ZoomOut()
{
	return m_camera->ZoomOut();
}

bool Graphics::CameraLeft()
{
	return m_camera->CameraLeft();
}

bool Graphics::CameraRight()
{
	return m_camera->CameraRight();
}

//Function to move the cube
void Graphics::PlungerFire()
{
	physicsEngine.PlungerFire();
}


